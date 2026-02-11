bnxt_init_chip(struct bnxt *bp, bool irq_re_init)
{
	struct bnxt_vnic_info *vnic = &bp->vnic_info[0];
	int rc = 0;
	unsigned int rx_nr_rings = bp->rx_nr_rings;

	if (irq_re_init) {
		rc = bnxt_hwrm_stat_ctx_alloc(bp);
		if (rc) {
			netdev_err(bp->dev, "hwrm stat ctx alloc failure rc: %x\n",
				   rc);
			goto err_out;
		}
	}

	rc = bnxt_hwrm_ring_alloc(bp);
	if (rc) {
		netdev_err(bp->dev, "hwrm ring alloc failure rc: %x\n", rc);
		goto err_out;
	}

	rc = bnxt_hwrm_ring_grp_alloc(bp);
	if (rc) {
		netdev_err(bp->dev, "hwrm_ring_grp alloc failure: %x\n", rc);
		goto err_out;
	}

	if (BNXT_CHIP_TYPE_NITRO_A0(bp))
		rx_nr_rings--;


	rc = bnxt_hwrm_vnic_alloc(bp, 0, 0, rx_nr_rings);
	if (rc) {
		netdev_err(bp->dev, "hwrm vnic alloc failure rc: %x\n", rc);
		goto err_out;
	}

	rc = bnxt_setup_vnic(bp, 0);
	if (rc)
		goto err_out;

	if (bp->flags & BNXT_FLAG_RFS) {
		rc = bnxt_alloc_rfs_vnics(bp);
		if (rc)
			goto err_out;
	}

	if (bp->flags & BNXT_FLAG_TPA) {
		rc = bnxt_set_tpa(bp, true);
		if (rc)
			goto err_out;
	}

	if (BNXT_VF(bp))
		bnxt_update_vf_mac(bp);


	rc = bnxt_hwrm_set_vnic_filter(bp, 0, 0, bp->dev->dev_addr);
	if (rc) {
		netdev_err(bp->dev, "HWRM vnic filter failure rc: %x\n", rc);
		goto err_out;
	}
	vnic->uc_filter_count = 1;

	vnic->rx_mask = CFA_L2_SET_RX_MASK_REQ_MASK_BCAST;

	if ((bp->dev->flags & IFF_PROMISC) && bnxt_promisc_ok(bp))
		vnic->rx_mask |= CFA_L2_SET_RX_MASK_REQ_MASK_PROMISCUOUS;

	if (bp->dev->flags & IFF_ALLMULTI) {
		vnic->rx_mask |= CFA_L2_SET_RX_MASK_REQ_MASK_ALL_MCAST;
		vnic->mc_list_count = 0;
	} else {
		u32 mask = 0;

		bnxt_mc_list_updated(bp, &mask);
		vnic->rx_mask |= mask;
	}

	rc = bnxt_cfg_rx_mode(bp);
	if (rc)
		goto err_out;

	rc = bnxt_hwrm_set_coal(bp);
	if (rc)
		netdev_warn(bp->dev, "HWRM set coalescing failure rc: %x\n",
				rc);

	if (BNXT_CHIP_TYPE_NITRO_A0(bp)) {
		rc = bnxt_setup_nitroa0_vnic(bp);
		if (rc)
			netdev_err(bp->dev, "Special vnic setup failure for NS2 A0 rc: %x\n",
				   rc);
	}

	if (BNXT_VF(bp)) {
		bnxt_hwrm_func_qcfg(bp);
		netdev_update_features(bp->dev);
	}

	return 0;

err_out:
	bnxt_hwrm_resource_free(bp, 0, true);

	return rc;
}
