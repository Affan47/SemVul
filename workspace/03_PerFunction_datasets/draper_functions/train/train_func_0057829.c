i40e_shutdown(struct pci_dev *pdev)
{
	struct i40e_pf *pf = pci_get_drvdata(pdev);
	struct i40e_hw *hw = &pf->hw;

	set_bit(__I40E_SUSPENDED, &pf->state);
	set_bit(__I40E_DOWN, &pf->state);
	rtnl_lock();
	i40e_prep_for_reset(pf);
	rtnl_unlock();

	wr32(hw, I40E_PFPM_APM, (pf->wol_en ? I40E_PFPM_APM_APME_MASK : 0));
	wr32(hw, I40E_PFPM_WUFC, (pf->wol_en ? I40E_PFPM_WUFC_MAG_MASK : 0));

	del_timer_sync(&pf->service_timer);
	cancel_work_sync(&pf->service_task);
	i40e_fdir_teardown(pf);

	rtnl_lock();
	i40e_prep_for_reset(pf);
	rtnl_unlock();

	wr32(hw, I40E_PFPM_APM,
	     (pf->wol_en ? I40E_PFPM_APM_APME_MASK : 0));
	wr32(hw, I40E_PFPM_WUFC,
	     (pf->wol_en ? I40E_PFPM_WUFC_MAG_MASK : 0));

	i40e_clear_interrupt_scheme(pf);

	if (system_state == SYSTEM_POWER_OFF) {
		pci_wake_from_d3(pdev, pf->wol_en);
		pci_set_power_state(pdev, PCI_D3hot);
	}
}
