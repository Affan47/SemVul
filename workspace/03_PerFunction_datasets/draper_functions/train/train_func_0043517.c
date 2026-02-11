CDB___txn_init(dbenv, tmgrp)
	DB_ENV *dbenv;
	DB_TXNMGR *tmgrp;
{
	DB_TXNREGION *region;
	int ret;

	if ((ret = CDB___db_shalloc(tmgrp->reginfo.addr,
	    sizeof(DB_TXNREGION), 0, &tmgrp->reginfo.primary)) != 0)
		return (ret);
	tmgrp->reginfo.rp->primary =
	    R_OFFSET(&tmgrp->reginfo, tmgrp->reginfo.primary);
	region = tmgrp->reginfo.primary;
	memset(region, 0, sizeof(*region));

	region->maxtxns = dbenv->tx_max;
	region->last_txnid = TXN_MINIMUM;
	ZERO_LSN(region->pending_ckp);
	ZERO_LSN(region->last_ckp);
	region->time_ckp = time(NULL);


	region->logtype = 0;
	region->locktype = 0;
	region->naborts = 0;
	region->ncommits = 0;
	region->nbegins = 0;
	region->nactive = 0;
	region->maxnactive = 0;

	SH_TAILQ_INIT(&region->active_txn);

	return (0);
}
