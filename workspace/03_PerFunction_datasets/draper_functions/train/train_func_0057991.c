bnxt_setup_int_mode(struct bnxt *bp)
{
	int rc;

	if (bp->flags & BNXT_FLAG_USING_MSIX)
		bnxt_setup_msix(bp);
	else
		bnxt_setup_inta(bp);

	rc = bnxt_set_real_num_queues(bp);
	return rc;
}
