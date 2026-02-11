bnxt_set_tpa(struct bnxt *bp, bool set_tpa)
{
	int rc, i;
	u32 tpa_flags = 0;

	if (set_tpa)
		tpa_flags = bp->flags & BNXT_FLAG_TPA;
	for (i = 0; i < bp->nr_vnics; i++) {
		rc = bnxt_hwrm_vnic_set_tpa(bp, i, tpa_flags);
		if (rc) {
			netdev_err(bp->dev, "hwrm vnic set tpa failure rc for vnic %d: %x\n",
				   i, rc);
			return rc;
		}
	}
	return 0;
}
