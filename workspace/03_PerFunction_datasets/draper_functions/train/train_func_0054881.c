asd_arp2_err(struct asd_ha_struct *asd_ha, u32 dchstatus)
{
	static const char *halt_code[256] = {
		"UNEXPECTED_INTERRUPT0",
		"UNEXPECTED_INTERRUPT1",
		"UNEXPECTED_INTERRUPT2",
		"UNEXPECTED_INTERRUPT3",
		"UNEXPECTED_INTERRUPT4",
		"UNEXPECTED_INTERRUPT5",
		"UNEXPECTED_INTERRUPT6",
		"UNEXPECTED_INTERRUPT7",
		"UNEXPECTED_INTERRUPT8",
		"UNEXPECTED_INTERRUPT9",
		"UNEXPECTED_INTERRUPT10",
		[11 ... 19] = "unknown[11,19]",
		"NO_FREE_SCB_AVAILABLE",
		"INVALID_SCB_OPCODE",
		"INVALID_MBX_OPCODE",
		"INVALID_ATA_STATE",
		"ATA_QUEUE_FULL",
		"ATA_TAG_TABLE_FAULT",
		"ATA_TAG_MASK_FAULT",
		"BAD_LINK_QUEUE_STATE",
		"DMA2CHIM_QUEUE_ERROR",
		"EMPTY_SCB_LIST_FULL",
		"unknown[30]",
		"IN_USE_SCB_ON_FREE_LIST",
		"BAD_OPEN_WAIT_STATE",
		"INVALID_STP_AFFILIATION",
		"unknown[34]",
		"EXEC_QUEUE_ERROR",
		"TOO_MANY_EMPTIES_NEEDED",
		"EMPTY_REQ_QUEUE_ERROR",
		"Q_MONIRTT_MGMT_ERROR",
		"TARGET_MODE_FLOW_ERROR",
		"DEVICE_QUEUE_NOT_FOUND",
		"START_IRTT_TIMER_ERROR",
		"ABORT_TASK_ILLEGAL_REQ",
		[43 ... 255] = "unknown[43,255]"
	};

	if (dchstatus & CSEQINT) {
		u32 arp2int = asd_read_reg_dword(asd_ha, CARP2INT);

		if (arp2int & (ARP2WAITTO|ARP2ILLOPC|ARP2PERR|ARP2CIOPERR)) {
			asd_printk("%s: CSEQ arp2int:0x%x\n",
				   pci_name(asd_ha->pcidev),
				   arp2int);
		} else if (arp2int & ARP2HALTC)
			asd_printk("%s: CSEQ halted: %s\n",
				   pci_name(asd_ha->pcidev),
				   halt_code[(arp2int>>16)&0xFF]);
		else
			asd_printk("%s: CARP2INT:0x%x\n",
				   pci_name(asd_ha->pcidev),
				   arp2int);
	}
	if (dchstatus & LSEQINT_MASK) {
		int lseq;
		u8  lseq_mask = dchstatus & LSEQINT_MASK;

		for_each_sequencer(lseq_mask, lseq_mask, lseq) {
			u32 arp2int = asd_read_reg_dword(asd_ha,
							 LmARP2INT(lseq));
			if (arp2int & (ARP2WAITTO | ARP2ILLOPC | ARP2PERR
				       | ARP2CIOPERR)) {
				asd_printk("%s: LSEQ%d arp2int:0x%x\n",
					   pci_name(asd_ha->pcidev),
					   lseq, arp2int);

			} else if (arp2int & ARP2HALTC)
				asd_printk("%s: LSEQ%d halted: %s\n",
					   pci_name(asd_ha->pcidev),
					   lseq,halt_code[(arp2int>>16)&0xFF]);
			else
				asd_printk("%s: LSEQ%d ARP2INT:0x%x\n",
					   pci_name(asd_ha->pcidev), lseq,
					   arp2int);
		}
	}
	asd_chip_reset(asd_ha);
}
