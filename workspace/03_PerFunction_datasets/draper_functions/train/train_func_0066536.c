qlcnic_sriov_set_vf_vport_info(struct qlcnic_adapter *adapter,
					  u16 func)
{
	struct qlcnic_info defvp_info;
	int err;

	err = qlcnic_sriov_pf_cal_res_limit(adapter, &defvp_info, func);
	if (err)
		return -EIO;

	err = qlcnic_sriov_set_vf_acl(adapter, func);
	if (err)
		return err;

	return 0;
}
