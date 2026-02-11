CDB___bam_rsplit_print(notused1, dbtp, lsnp, notused2, notused3)
	DB_ENV *notused1;
	DBT *dbtp;
	DB_LSN *lsnp;
	int notused2;
	void *notused3;
{
	__bam_rsplit_args *argp;
	u_int32_t i;
	u_int ch;
	int ret;

	i = 0;
	ch = 0;
	notused1 = NULL;
	notused2 = 0;
	notused3 = NULL;

	if ((ret = CDB___bam_rsplit_read(dbtp->data, &argp)) != 0)
		return (ret);
	printf("[%lu][%lu]bam_rsplit: rec: %lu txnid %lx prevlsn [%lu][%lu]\n",
	    (u_long)lsnp->file,
	    (u_long)lsnp->offset,
	    (u_long)argp->type,
	    (u_long)argp->txnid->txnid,
	    (u_long)argp->prev_lsn.file,
	    (u_long)argp->prev_lsn.offset);
	printf("\tfileid: %lu\n", (u_long)argp->fileid);
	printf("\tpgno: %lu\n", (u_long)argp->pgno);
	printf("\tpgdbt: ");
	for (i = 0; i < argp->pgdbt.size; i++) {
		ch = ((u_int8_t *)argp->pgdbt.data)[i];
		if (isprint(ch) || ch == 0xa)
			putchar(ch);
		else
			printf("%#x ", ch);
	}
	printf("\n");
	printf("\tnrec: %lu\n", (u_long)argp->nrec);
	printf("\trootent: ");
	for (i = 0; i < argp->rootent.size; i++) {
		ch = ((u_int8_t *)argp->rootent.data)[i];
		if (isprint(ch) || ch == 0xa)
			putchar(ch);
		else
			printf("%#x ", ch);
	}
	printf("\n");
	printf("\trootlsn: [%lu][%lu]\n",
	    (u_long)argp->rootlsn.file, (u_long)argp->rootlsn.offset);
	printf("\n");
	CDB___os_free(argp, 0);
	return (0);
}
