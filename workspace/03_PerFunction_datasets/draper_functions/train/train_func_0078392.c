__memp_set_maxpgno(mfp, gbytes, bytes)
	MPOOLFILE *mfp;
	u_int32_t gbytes, bytes;
{
	if (gbytes == 0 && bytes <= mfp->pagesize)
		mfp->maxpgno = 0;
	else {
		mfp->maxpgno = (db_pgno_t)
		    (gbytes * (GIGABYTE / mfp->pagesize));

		mfp->maxpgno += (db_pgno_t)
		    ((bytes + mfp->pagesize - 1) / mfp->pagesize);

		mfp->maxpgno--;
	}
}
