cob_file_open (cob_file *f, char *filename, const int mode, const int sharing)
{
	FILE			*fp = NULL;
	struct linage_struct    *lingptr;
#ifdef HAVE_FCNTL
	int			ret;
	struct flock		lock;
#endif


	switch (mode) {
	case COB_OPEN_INPUT:
#if !defined(_WIN32) || defined(_MSC_VER)
		if (f->organization == COB_ORG_LINE_SEQUENTIAL)
			fp = fopen (filename, "r");
		else
#endif
			fp = fopen (filename, "rb");
		break;
	case COB_OPEN_OUTPUT:
		if (f->organization == COB_ORG_RELATIVE)
			fp = fopen (filename, "wb+");
#if !defined(_WIN32) || defined(_MSC_VER)
		else if (f->organization == COB_ORG_LINE_SEQUENTIAL)
			fp = fopen (filename, "w");
#endif
		else
			fp = fopen (filename, "wb");
		break;
	case COB_OPEN_I_O:
#if !defined(_WIN32) || defined(_MSC_VER)
		if (f->organization == COB_ORG_LINE_SEQUENTIAL)
			fp = fopen (filename, "r+");
		else
#endif
			fp = fopen (filename, "rb+");
		break;
	case COB_OPEN_EXTEND:
#if !defined(_WIN32) || defined(_MSC_VER)
		if (f->organization == COB_ORG_LINE_SEQUENTIAL)
			fp = fopen (filename, "a+");
		else
#endif
			fp = fopen (filename, "ab+");
		break;
	}
	if (fp == NULL) {
		return errno;
	}

	if (mode == COB_OPEN_EXTEND) {
		fseek (fp, (off_t) 0, SEEK_END);
	}

#ifdef HAVE_FCNTL

	if (memcmp (filename, "/dev/", 5)) {
		memset ((unsigned char *)&lock, 0, sizeof (struct flock));
		lock.l_type = (sharing || mode == COB_OPEN_OUTPUT) ? F_WRLCK : F_RDLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		if (fcntl (fileno (fp), F_SETLK, &lock) < 0) {
			ret = errno;
			fclose (fp);
			return ret;
		}
	}
#endif

	f->file = fp;
	if (unlikely(f->flag_select_features & COB_SELECT_LINAGE)) {
		if (file_linage_check (f)) {
			return COB_LINAGE_INVALID;
		}
		f->flag_needs_top = 1;
		lingptr = (struct linage_struct *)(f->linorkeyptr);
		cob_set_int (lingptr->linage_ctr, 1);
	}
	return 0;
}
