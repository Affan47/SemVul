emiturl(struct msg2html_textplain_info *info)
{
	size_t url_size=info->urlindex;
	char save_char;

	text_process_decor_apostrophe(info);
	set_text_decor(info, info->text_decor_state);

	info->text_url_handler=text_contents_notalpha;

	while (url_size > 0)
	{
		if (strchr(",.;:", info->urlbuf[url_size-1]) == NULL)
			break;
		--url_size;
	}

	info->urlbuf[info->urlindex]=0;

	save_char=info->urlbuf[url_size];
	info->urlbuf[url_size]=0;
	doemiturl(info);
	info->urlbuf[url_size]=save_char;

	emit_char_buffer(info, info->urlbuf+url_size,
			 strlen(info->urlbuf+url_size),
			 text_process_decor);
}
