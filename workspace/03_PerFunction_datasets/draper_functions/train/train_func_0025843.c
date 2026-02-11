text_contents_notalpha(struct msg2html_textplain_info *info,
				     const unicode_char *txt,
				     size_t txt_size)
{
	size_t i;

	if (!txt)
		return 0;

	for (i=0; i<txt_size; i++)
	{
		if (txt[i] >= 'a' && txt[i] <= 'z')
		{


			info->urlindex=0;
			info->text_url_handler=text_contents_checkurl;
			break;
		}
	}

	if (i)
		text_process_decor(info, txt, i);

	return i;
}
