i40e_free_vfs(struct i40e_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	u32 reg_idx, bit_idx;
	int i, tmp, vf_id;

	if (!pf->vf)
		return;
	while (test_and_set_bit(__I40E_VF_DISABLE, &pf->state))
		usleep_range(1000, 2000);

	for (i = 0; i < pf->num_alloc_vfs; i++)
		if (test_bit(I40E_VF_STAT_INIT, &pf->vf[i].vf_states))
			i40e_vsi_control_rings(pf->vsi[pf->vf[i].lan_vsi_idx],
					       false);

	for (i = 0; i < pf->num_alloc_vfs; i++)
		if (test_bit(I40E_VF_STAT_INIT, &pf->vf[i].vf_states))
			i40e_vsi_control_rings(pf->vsi[pf->vf[i].lan_vsi_idx],
					       false);


	if (!pci_vfs_assigned(pf->pdev))
		pci_disable_sriov(pf->pdev);
	else
		dev_warn(&pf->pdev->dev, "VFs are assigned - not disabling SR-IOV\n");

	msleep(20);


	tmp = pf->num_alloc_vfs;
	pf->num_alloc_vfs = 0;
	for (i = 0; i < tmp; i++) {
		if (test_bit(I40E_VF_STAT_INIT, &pf->vf[i].vf_states))
			i40e_free_vf_res(&pf->vf[i]);

		i40e_disable_vf_mappings(&pf->vf[i]);
	}

	kfree(pf->vf);
	pf->vf = NULL;


	if (!pci_vfs_assigned(pf->pdev)) {


		for (vf_id = 0; vf_id < tmp; vf_id++) {
			reg_idx = (hw->func_caps.vf_base_id + vf_id) / 32;
			bit_idx = (hw->func_caps.vf_base_id + vf_id) % 32;
			wr32(hw, I40E_GLGEN_VFLRSTAT(reg_idx), BIT(bit_idx));
		}
	}
	clear_bit(__I40E_VF_DISABLE, &pf->state);
}
