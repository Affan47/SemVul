bnxt_setup_vnic(struct bnxt *bp, u16 vnic_id)
{
	int rc;


	rc = bnxt_hwrm_vnic_ctx_alloc(bp, vnic_id);
	if (rc) {
		netdev_err(bp->dev, "hwrm vnic %d alloc failure rc: %x\n",
			   vnic_id, rc);
		goto vnic_setup_err;
	}
	bp->rsscos_nr_ctxs++;


	rc = bnxt_hwrm_vnic_cfg(bp, vnic_id);
	if (rc) {
		netdev_err(bp->dev, "hwrm vnic %d cfg failure rc: %x\n",
			   vnic_id, rc);
		goto vnic_setup_err;
	}


	rc = bnxt_hwrm_vnic_set_rss(bp, vnic_id, true);
	if (rc) {
		netdev_err(bp->dev, "hwrm vnic %d set rss failure rc: %x\n",
			   vnic_id, rc);
		goto vnic_setup_err;
	}

	if (bp->flags & BNXT_FLAG_AGG_RINGS) {
		rc = bnxt_hwrm_vnic_set_hds(bp, vnic_id);
		if (rc) {
			netdev_err(bp->dev, "hwrm vnic %d set hds failure rc: %x\n",
				   vnic_id, rc);
		}
	}

vnic_setup_err:
	return rc;
}
