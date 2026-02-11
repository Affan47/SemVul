qlcnic_sriov_validate_cfg_macvlan(struct qlcnic_adapter *adapter,
					     struct qlcnic_vf_info *vf,
					     struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_vport *vp = vf->vp;
	u8 op, new_op;

	if (!(cmd->req.arg[1] & BIT_8))
		return -EINVAL;

	cmd->req.arg[1] |= (vf->vp->handle << 16);
	cmd->req.arg[1] |= BIT_31;

	if (vp->vlan_mode == QLC_PVID_MODE) {
		op = cmd->req.arg[1] & 0x7;
		cmd->req.arg[1] &= ~0x7;
		new_op = (op == QLCNIC_MAC_ADD || op == QLCNIC_MAC_VLAN_ADD) ?
			 QLCNIC_MAC_VLAN_ADD : QLCNIC_MAC_VLAN_DEL;
		cmd->req.arg[3] |= vp->pvid << 16;
		cmd->req.arg[1] |= new_op;
	}

	return 0;
}
