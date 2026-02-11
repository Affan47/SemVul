k12text_seek_read(wtap *wth, gint64 seek_off, struct wtap_pkthdr *phdr, Buffer *buf, int *err, char **err_info)
{
	if ( file_seek(wth->random_fh, seek_off, SEEK_SET, err) == -1) {
		return FALSE;
	}
	k12text_reset(wth->random_fh);

	BEGIN(NEXT_FRAME);
	K12Text_lex();

	if (ok_frame == FALSE) {
		*err = WTAP_ERR_BAD_FILE;
		if (at_eof) {

			*err_info = g_strdup("Unexpected EOF (program error ?)");
		} else {
			*err_info = error_str;
		}
		return FALSE;
	}

	if (!k12text_set_headers(phdr, err, err_info))
		return FALSE;

	ws_buffer_assure_space(buf, phdr->caplen);
	memcpy(ws_buffer_start_ptr(buf), bb, phdr->caplen);

	return TRUE;
}
