qlcnic_sriov_pf_channel_cfg_cmd(struct qlcnic_bc_trans *trans,
					   struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_vf_info *vf = trans->vf;
	struct qlcnic_vport *vp = vf->vp;
	struct qlcnic_adapter *adapter;
	struct qlcnic_sriov *sriov;
	u16 func = vf->pci_func;
	size_t size;
	int err;

	adapter = vf->adapter;
	sriov = adapter->ahw->sriov;

	if (trans->req_hdr->cmd_op == QLCNIC_BC_CMD_CHANNEL_INIT) {
		err = qlcnic_sriov_pf_config_vport(adapter, 1, func);
		if (!err) {
			err = qlcnic_sriov_set_vf_vport_info(adapter, func);
			if (err)
				qlcnic_sriov_pf_config_vport(adapter, 0, func);
		}
	} else {
		if (vp->vlan_mode == QLC_GUEST_VLAN_MODE) {
			size = sizeof(*vf->sriov_vlans);
			size = size * sriov->num_allowed_vlans;
			memset(vf->sriov_vlans, 0, size);
		}

		err = qlcnic_sriov_pf_config_vport(adapter, 0, func);
	}

	if (err)
		goto err_out;

	cmd->rsp.arg[0] |= (1 << 25);

	if (trans->req_hdr->cmd_op == QLCNIC_BC_CMD_CHANNEL_INIT)
		set_bit(QLC_BC_VF_STATE, &vf->state);
	else
		clear_bit(QLC_BC_VF_STATE, &vf->state);

	return err;

err_out:
	cmd->rsp.arg[0] |= (2 << 25);
	return err;
}
