mf_do_open(mfp, fname, new)
	MEMFILE		*mfp;
	char_u		*fname;
	int			new;
{
	mfp->mf_fname = fname;


#ifdef KANJI
	if (FullName(fileconvsto(fname), NameBuff, MAXPATHL) == FAIL)
#else
	if (FullName(fname, NameBuff, MAXPATHL) == FAIL)
#endif
		mfp->mf_xfname = NULL;
	else
#ifdef KANJI
		mfp->mf_xfname = strsave(fileconvsfrom(NameBuff));
#else
		mfp->mf_xfname = strsave(NameBuff);
#endif


#ifdef KANJI
	mfp->mf_fd = open(fileconvsto(fname), new ? (O_CREAT | O_RDWR | O_TRUNC) : (O_RDONLY)
#else
	mfp->mf_fd = open((char *)fname, new ? (O_CREAT | O_RDWR | O_TRUNC) : (O_RDONLY)
#endif

#ifdef AMIGA
					);
#endif
#ifdef UNIX
# ifdef SCO
					, (mode_t)0600);
# else
					, 0600);
# endif
#endif
#ifdef MSDOS
					, S_IREAD | S_IWRITE);
#endif


	if (mfp->mf_fd < 0)
	{
		free(fname);
		free(mfp->mf_xfname);
		mfp->mf_fname = NULL;
		mfp->mf_xfname = NULL;
	}
}
