handle_commit_msg(struct strbuf *line)
{
	static int still_looking = 1;

	if (!cmitmsg)
		return 0;

	if (still_looking) {
		strbuf_ltrim(line);
		if (!line->len)
			return 0;
		if ((still_looking = check_header(line, s_hdr_data, 0)) != 0)
			return 0;
	}


	if (metainfo_charset)
		convert_to_utf8(line, charset.buf);

	if (patchbreak(line)) {
		fclose(cmitmsg);
		cmitmsg = NULL;
		return 1;
	}

	fputs(line->buf, cmitmsg);
	return 0;
}
