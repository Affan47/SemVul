mf_open_file(mfp, fname)
    memfile_T	*mfp;
    char_u	*fname;
{
    mf_do_open(mfp, fname, O_RDWR|O_CREAT|O_EXCL);

    if (mfp->mf_fd < 0)
	return FAIL;

    mfp->mf_dirty = TRUE;
    return OK;
}
