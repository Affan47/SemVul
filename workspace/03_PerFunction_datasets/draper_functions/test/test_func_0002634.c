pm8001_request_irq(struct pm8001_hba_info *pm8001_ha)
{
	struct pci_dev *pdev;
	int rc;

	pdev = pm8001_ha->pdev;

#ifdef PM8001_USE_MSIX
	if (pdev->msix_cap && pci_msi_enabled())
		return pm8001_setup_msix(pm8001_ha);
	else {
		PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("MSIX not supported!!!\n"));
		goto intx;
	}
#endif

intx:

	pm8001_ha->irq_vector[0].irq_id = 0;
	pm8001_ha->irq_vector[0].drv_inst = pm8001_ha;
	rc = request_irq(pdev->irq, pm8001_interrupt_handler_intx, IRQF_SHARED,
		DRV_NAME, SHOST_TO_SAS_HA(pm8001_ha->shost));
	return rc;
}
