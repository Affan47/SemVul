ml_open_files()
{
	BUF			*buf;
	MEMFILE		*mfp;
	char_u		*fname;
	int			i;

	for (buf = firstbuf; buf != NULL; buf = buf->b_next)
	{
		mfp = buf->b_ml.ml_mfp;
		if (mfp == NULL || mfp->mf_fd >= 0)
			continue;


		fname = findswapname(buf, FALSE);


		if (fname != NULL && *p_dir != NUL && *p_dir != '>')
			i = 0;
		else
			i = 1;
		for ( ; i < 2 && mf_open_file(mfp, fname) == FAIL; ++i)
		{
			fname = findswapname(buf, TRUE);
		}
		if (mfp->mf_fname == NULL)
		{

			if (EMSG2("Unable to open swap file for \"%s\", recovery impossible",
					buf->b_xfilename == NULL ? (char_u *)"No File"
											 : buf->b_xfilename))
			{
				msg_outchar('\n');
				wait_return(FALSE);
			}
		}
	}
}
