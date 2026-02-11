beiscsi_ue_detect(struct beiscsi_hba *phba)
{
	uint32_t ue_hi = 0, ue_lo = 0;
	uint32_t ue_mask_hi = 0, ue_mask_lo = 0;
	uint8_t i = 0;

	if (phba->ue_detected)
		return;

	pci_read_config_dword(phba->pcidev,
			      PCICFG_UE_STATUS_LOW, &ue_lo);
	pci_read_config_dword(phba->pcidev,
			      PCICFG_UE_STATUS_MASK_LOW,
			      &ue_mask_lo);
	pci_read_config_dword(phba->pcidev,
			      PCICFG_UE_STATUS_HIGH,
			      &ue_hi);
	pci_read_config_dword(phba->pcidev,
			      PCICFG_UE_STATUS_MASK_HI,
			      &ue_mask_hi);

	ue_lo = (ue_lo & ~ue_mask_lo);
	ue_hi = (ue_hi & ~ue_mask_hi);


	if (ue_lo || ue_hi) {
		phba->ue_detected = true;
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
			    "BG_%d : Error detected on the adapter\n");
	}

	if (ue_lo) {
		for (i = 0; ue_lo; ue_lo >>= 1, i++) {
			if (ue_lo & 1)
				beiscsi_log(phba, KERN_ERR,
					    BEISCSI_LOG_CONFIG,
					    "BG_%d : UE_LOW %s bit set\n",
					    desc_ue_status_low[i]);
		}
	}

	if (ue_hi) {
		for (i = 0; ue_hi; ue_hi >>= 1, i++) {
			if (ue_hi & 1)
				beiscsi_log(phba, KERN_ERR,
					    BEISCSI_LOG_CONFIG,
					    "BG_%d : UE_HIGH %s bit set\n",
					    desc_ue_status_hi[i]);
		}
	}
}
