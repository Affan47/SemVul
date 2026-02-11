qed_start_vport(struct qed_dev *cdev,
			   u8 vport_id,
			   u16 mtu,
			   u8 drop_ttl0_flg,
			   u8 inner_vlan_removal_en_flg)
{
	int rc, i;

	for_each_hwfn(cdev, i) {
		struct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		rc = qed_sp_vport_start(p_hwfn,
					p_hwfn->hw_info.concrete_fid,
					p_hwfn->hw_info.opaque_fid,
					vport_id,
					mtu,
					drop_ttl0_flg,
					inner_vlan_removal_en_flg);

		if (rc) {
			DP_ERR(cdev, "Failed to start VPORT\n");
			return rc;
		}

		qed_hw_start_fastpath(p_hwfn);

		DP_VERBOSE(cdev, (QED_MSG_SPQ | NETIF_MSG_IFUP),
			   "Started V-PORT %d with MTU %d\n",
			   vport_id, mtu);
	}

	qed_reset_vport_stats(cdev);

	return 0;
}
