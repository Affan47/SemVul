CDB___ham_groupalloc_print(notused1, dbtp, lsnp, notused2, notused3)
	DB_ENV *notused1;
	DBT *dbtp;
	DB_LSN *lsnp;
	int notused2;
	void *notused3;
{
	__ham_groupalloc_args *argp;
	u_int32_t i;
	u_int ch;
	int ret;

	i = 0;
	ch = 0;
	notused1 = NULL;
	notused2 = 0;
	notused3 = NULL;

	if ((ret = CDB___ham_groupalloc_read(dbtp->data, &argp)) != 0)
		return (ret);
	printf("[%lu][%lu]ham_groupalloc: rec: %lu txnid %lx prevlsn [%lu][%lu]\n",
	    (u_long)lsnp->file,
	    (u_long)lsnp->offset,
	    (u_long)argp->type,
	    (u_long)argp->txnid->txnid,
	    (u_long)argp->prev_lsn.file,
	    (u_long)argp->prev_lsn.offset);
	printf("\tfileid: %lu\n", (u_long)argp->fileid);
	printf("\tpgno: %lu\n", (u_long)argp->pgno);
	printf("\tmetalsn: [%lu][%lu]\n",
	    (u_long)argp->metalsn.file, (u_long)argp->metalsn.offset);
	printf("\tmmetalsn: [%lu][%lu]\n",
	    (u_long)argp->mmetalsn.file, (u_long)argp->mmetalsn.offset);
	printf("\tstart_pgno: %lu\n", (u_long)argp->start_pgno);
	printf("\tnum: %lu\n", (u_long)argp->num);
	printf("\n");
	CDB___os_free(argp, 0);
	return (0);
}
