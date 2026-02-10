qlcnic_sriov_pf_reinit(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int err;

	if (!qlcnic_sriov_enable_check(adapter))
		return 0;

	ahw->op_mode = QLCNIC_SRIOV_PF_FUNC;

	err = qlcnic_sriov_pf_init(adapter);
	if (err)
		return err;

	dev_info(&adapter->pdev->dev, "%s: op_mode %d\n",
		 __func__, ahw->op_mode);
	return err;
}
