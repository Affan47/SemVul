beiscsi_eeh_resume(struct pci_dev *pdev)
{
	int ret = 0, i;
	struct be_eq_obj *pbe_eq;
	struct beiscsi_hba *phba = NULL;
	struct hwi_controller *phwi_ctrlr;
	struct hwi_context_memory *phwi_context;

	phba = (struct beiscsi_hba *)pci_get_drvdata(pdev);
	pci_save_state(pdev);

	if (enable_msix)
		find_num_cpus(phba);
	else
		phba->num_cpus = 1;

	if (enable_msix) {
		beiscsi_msix_enable(phba);
		if (!phba->msix_enabled)
			phba->num_cpus = 1;
	}

	ret = beiscsi_cmd_reset_function(phba);
	if (ret) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : Reset Failed\n");
		goto ret_err;
	}

	ret = be_chk_reset_complete(phba);
	if (ret) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : Failed to get out of reset.\n");
		goto ret_err;
	}

	beiscsi_get_params(phba);
	phba->shost->max_id = phba->params.cxns_per_ctrl;
	phba->shost->can_queue = phba->params.ios_per_ctrl;
	ret = hwi_init_controller(phba);

	for (i = 0; i < MAX_MCC_CMD; i++) {
		init_waitqueue_head(&phba->ctrl.mcc_wait[i + 1]);
		phba->ctrl.mcc_tag[i] = i + 1;
		phba->ctrl.mcc_numtag[i + 1] = 0;
		phba->ctrl.mcc_tag_available++;
	}

	phwi_ctrlr = phba->phwi_ctrlr;
	phwi_context = phwi_ctrlr->phwi_ctxt;

	for (i = 0; i < phba->num_cpus; i++) {
		pbe_eq = &phwi_context->be_eq[i];
		blk_iopoll_init(&pbe_eq->iopoll, be_iopoll_budget,
				be_iopoll);
		blk_iopoll_enable(&pbe_eq->iopoll);
	}

	i = (phba->msix_enabled) ? i : 0;

	pbe_eq = &phwi_context->be_eq[i];
	INIT_WORK(&pbe_eq->work_cqs, beiscsi_process_all_cqs);

	ret = beiscsi_init_irqs(phba);
	if (ret < 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : beiscsi_eeh_resume - "
			    "Failed to beiscsi_init_irqs\n");
		goto ret_err;
	}

	hwi_enable_intr(phba);
	phba->state &= ~BE_ADAPTER_PCI_ERR;

	return;
ret_err:
	beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
		    "BM_%d : AER EEH Resume Failed\n");
}
