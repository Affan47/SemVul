fm10k_iov_suspend(struct pci_dev *pdev)
{
	struct fm10k_intfc *interface = pci_get_drvdata(pdev);
	struct fm10k_iov_data *iov_data = interface->iov_data;
	struct fm10k_hw *hw = &interface->hw;
	int num_vfs, i;


	num_vfs = iov_data ? iov_data->num_vfs : 0;


	fm10k_write_reg(hw, FM10K_DGLORTMAP(fm10k_dglort_vf_rss),
			FM10K_DGLORTMAP_NONE);


	for (i = 0; i < num_vfs; i++) {
		struct fm10k_vf_info *vf_info = &iov_data->vf_info[i];

		hw->iov.ops.reset_resources(hw, vf_info);
		hw->iov.ops.reset_lport(hw, vf_info);
	}
}
