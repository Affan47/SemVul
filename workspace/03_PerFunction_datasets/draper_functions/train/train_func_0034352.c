ipath_snapshot_counters(struct ipath_devdata *dd, u64 *swords,
			    u64 *rwords, u64 *spkts, u64 *rpkts,
			    u64 *xmit_wait)
{
	int ret;

	if (!(dd->ipath_flags & IPATH_INITTED)) {

		ret = -EINVAL;
		goto bail;
	}
	*swords = ipath_snap_cntr(dd, dd->ipath_cregs->cr_wordsendcnt);
	*rwords = ipath_snap_cntr(dd, dd->ipath_cregs->cr_wordrcvcnt);
	*spkts = ipath_snap_cntr(dd, dd->ipath_cregs->cr_pktsendcnt);
	*rpkts = ipath_snap_cntr(dd, dd->ipath_cregs->cr_pktrcvcnt);
	*xmit_wait = ipath_snap_cntr(dd, dd->ipath_cregs->cr_sendstallcnt);

	ret = 0;

bail:
	return ret;
}
