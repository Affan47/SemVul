close_buffer(buf, free_buf, remove)
	BUF		*buf;
	int		free_buf;
	int		remove;
{
	if (buf->b_nwindows > 0)
		--buf->b_nwindows;
	if (buf->b_nwindows > 0 || !free_buf)
	{
		if (buf == curbuf)
			u_sync();
		return;
	}

	buf_freeall(buf);


	if (buf->b_filename == NULL || remove)
	{
		free(buf->b_filename);
		free(buf->b_sfilename);
		if (buf->b_prev == NULL)
			firstbuf = buf->b_next;
		else
			buf->b_prev->b_next = buf->b_next;
		if (buf->b_next == NULL)
			lastbuf = buf->b_prev;
		else
			buf->b_next->b_prev = buf->b_prev;
#ifdef KANJI
		free(buf->b_p_jc);
#endif
#ifdef FEPCTRL
		free(buf->b_p_ji);
#endif
#ifdef TRACK
		free(buf->b_p_trs);
#endif
#if defined(KANJI) && defined(NT) && defined(SYNTAX)
		syn_clr(buf);
#endif
		free(buf);
	}
	else
		buf_clear(buf);
}
