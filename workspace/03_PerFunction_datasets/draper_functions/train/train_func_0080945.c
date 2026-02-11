insertbuf(c)
	int c;
{
	long i;


	breakcheck();
	if (got_int)
		return FAIL;

	if (!is_yank_buffer(c, FALSE))
		return FAIL;

	if (c == '.')
	{
		stuff_inserted(NUL, 1L, TRUE);
		return OK;
	}

	if (c == '%')
	{
		if (check_fname() == FAIL)
			return FAIL;
		stuffReadbuff(curbuf->b_xfilename);
		return OK;
	}

	if (c == ':')
	{
		if (last_cmdline == NULL)
		{
			EMSG(e_nolastcmd);
			return FAIL;
		}
		stuffReadbuff(last_cmdline);
		return OK;
	}

	yankbuffer = c;
	get_yank_buffer(FALSE);
	if (y_current->y_array == NULL)
		return FAIL;

	for (i = 0; i < y_current->y_size; ++i)
	{
		stuffReadbuff(y_current->y_array[i]);

		if (y_current->y_type == MLINE || i < y_current->y_size - 1)
			stuffReadbuff((char_u *)"\n");
	}
	return OK;
}
