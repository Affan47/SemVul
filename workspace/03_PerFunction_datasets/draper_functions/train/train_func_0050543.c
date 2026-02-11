qlcnic_sriov_send_bc_cmd(struct qlcnic_adapter *adapter,
				    struct qlcnic_bc_trans *trans, int pci_func)
{
	struct qlcnic_vf_info *vf;
	int err, index = qlcnic_sriov_func_to_index(adapter, pci_func);

	if (index < 0)
		return -EIO;

	vf = &adapter->ahw->sriov->vf_info[index];
	trans->vf = vf;
	trans->func_id = pci_func;

	if (!test_bit(QLC_BC_VF_STATE, &vf->state)) {
		if (qlcnic_sriov_pf_check(adapter))
			return -EIO;
		if (qlcnic_sriov_vf_check(adapter) &&
		    trans->cmd_id != QLCNIC_BC_CMD_CHANNEL_INIT)
			return -EIO;
	}

	mutex_lock(&vf->send_cmd_lock);
	vf->send_cmd = trans;
	err = __qlcnic_sriov_send_bc_msg(trans, vf, QLC_BC_COMMAND);
	qlcnic_sriov_clear_trans(vf, trans, QLC_BC_COMMAND);
	mutex_unlock(&vf->send_cmd_lock);
	return err;
}
