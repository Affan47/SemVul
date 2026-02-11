CDB___ham_newpgno_print(notused1, dbtp, lsnp, notused2, notused3)
	DB_ENV *notused1;
	DBT *dbtp;
	DB_LSN *lsnp;
	int notused2;
	void *notused3;
{
	__ham_newpgno_args *argp;
	u_int32_t i;
	u_int ch;
	int ret;

	i = 0;
	ch = 0;
	notused1 = NULL;
	notused2 = 0;
	notused3 = NULL;

	if ((ret = CDB___ham_newpgno_read(dbtp->data, &argp)) != 0)
		return (ret);
	printf("[%lu][%lu]ham_newpgno: rec: %lu txnid %lx prevlsn [%lu][%lu]\n",
	    (u_long)lsnp->file,
	    (u_long)lsnp->offset,
	    (u_long)argp->type,
	    (u_long)argp->txnid->txnid,
	    (u_long)argp->prev_lsn.file,
	    (u_long)argp->prev_lsn.offset);
	printf("\topcode: %lu\n", (u_long)argp->opcode);
	printf("\tfileid: %lu\n", (u_long)argp->fileid);
	printf("\tpgno: %lu\n", (u_long)argp->pgno);
	printf("\tfree_pgno: %lu\n", (u_long)argp->free_pgno);
	printf("\told_type: %lu\n", (u_long)argp->old_type);
	printf("\told_pgno: %lu\n", (u_long)argp->old_pgno);
	printf("\tnew_type: %lu\n", (u_long)argp->new_type);
	printf("\tpagelsn: [%lu][%lu]\n",
	    (u_long)argp->pagelsn.file, (u_long)argp->pagelsn.offset);
	printf("\tmetalsn: [%lu][%lu]\n",
	    (u_long)argp->metalsn.file, (u_long)argp->metalsn.offset);
	printf("\n");
	CDB___os_free(argp, 0);
	return (0);
}
