lpfc_sli4_brdreset(struct lpfc_hba *phba)
{
	struct lpfc_sli *psli = &phba->sli;
	uint16_t cfg_value;
	int rc = 0;


	lpfc_printf_log(phba, KERN_INFO, LOG_SLI,
			"0295 Reset HBA Data: x%x x%x x%x\n",
			phba->pport->port_state, psli->sli_flag,
			phba->hba_flag);


	phba->fc_eventTag = 0;
	phba->link_events = 0;
	phba->pport->fc_myDID = 0;
	phba->pport->fc_prevDID = 0;

	spin_lock_irq(&phba->hbalock);
	psli->sli_flag &= ~(LPFC_PROCESS_LA);
	phba->fcf.fcf_flag = 0;
	spin_unlock_irq(&phba->hbalock);


	if (phba->hba_flag & HBA_FW_DUMP_OP) {
		phba->hba_flag &= ~HBA_FW_DUMP_OP;
		return rc;
	}


	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"0389 Performing PCI function reset!\n");


	pci_read_config_word(phba->pcidev, PCI_COMMAND, &cfg_value);
	pci_write_config_word(phba->pcidev, PCI_COMMAND, (cfg_value &
			      ~(PCI_COMMAND_PARITY | PCI_COMMAND_SERR)));


	rc = lpfc_pci_function_reset(phba);
	lpfc_sli4_queue_destroy(phba);


	pci_write_config_word(phba->pcidev, PCI_COMMAND, cfg_value);

	return rc;
}
