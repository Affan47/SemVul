tg3_restart_fw(struct tg3 *tp, uint32_t state)
{
	uint32_t val;
	int i;

	tg3_write_mem(NIC_SRAM_FIRMWARE_MBOX,
		NIC_SRAM_FIRMWARE_MBOX_MAGIC1);

	for (i = 0; i < 100000; i++) {
		tg3_read_mem(NIC_SRAM_FIRMWARE_MBOX, &val);
		if (val == (uint32_t) ~NIC_SRAM_FIRMWARE_MBOX_MAGIC1)
			break;
		udelay(10);
	}
	if (i >= 100000 &&
		    !(tp->tg3_flags2 & TG3_FLG2_SUN_5704) &&
		    !(GET_ASIC_REV(tp->pci_chip_rev_id) == ASIC_REV_5787)) {
		printf ( "Firmware will not restart magic=%#x\n",
			val );
		return -ENODEV;
	}
	if (!(tp->tg3_flags & TG3_FLAG_ENABLE_ASF)) {
	  state = DRV_STATE_SUSPEND;
	}

	if ((tp->tg3_flags2 & TG3_FLG2_PCI_EXPRESS) &&
	    (tp->pci_chip_rev_id != CHIPREV_ID_5750_A0)) {

	  tg3_read_mem(0x7c00, &val);
	  tg3_write_mem(0x7c00, val | 0x02000000);
	}
	tg3_write_mem(NIC_SRAM_FW_DRV_STATE_MBOX, state);
	return 0;
}
