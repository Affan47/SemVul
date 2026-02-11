env_stats(DB_ENV *dbenvp)
{
	REGENV renv;
	REGION *rp, regs[1024];
	int n, ret;
	const char *lable;

	n = sizeof(regs) / sizeof(regs[0]);
	if ((ret = CDB___db_e_stat(dbenvp, &renv, regs, &n)) != 0)  {
		dbenvp->err(dbenvp, ret, "CDB___db_e_stat");
		return (1);
	}

	printf("%d.%d.%d\tEnvironment version.\n",
	    renv.majver, renv.minver, renv.patch);
	printf("%lx\tMagic number.\n", (u_long)renv.magic);
	printf("%d\tPanic value.\n", renv.panic);


	printf("%d\tReferences.\n", renv.refcnt - 1);

	dl("Locks granted without waiting.\n",
	    (u_long)renv.mutex.mutex_set_nowait);
	dl("Locks granted after waiting.\n",
	    (u_long)renv.mutex.mutex_set_wait);

	while (n > 0) {
		printf("%s\n", DB_LINE);
		rp = &regs[--n];
		switch (rp->id) {
		case REG_ID_ENV:
			lable = "Environment";
			break;
		case REG_ID_LOCK:
			lable = "Lock";
			break;
		case REG_ID_LOG:
			lable = "Log";
			break;
		case REG_ID_MPOOL:
			lable = "Mpool";
			break;
		case REG_ID_TXN:
			lable = "Txn";
			break;
		default:
			lable = "Unknown";
			break;
		}
		printf("%s Region: %d.\n", lable, rp->id);
		dl_bytes("Size.\n", (u_long)0, (u_long)0, (u_long)rp->size);
		printf("%d\tSegment ID.\n", rp->segid);
		dl("Locks granted without waiting.\n",
		    (u_long)rp->mutex.mutex_set_nowait);
		dl("Locks granted after waiting.\n",
		    (u_long)rp->mutex.mutex_set_wait);
	}

	return (0);
}
