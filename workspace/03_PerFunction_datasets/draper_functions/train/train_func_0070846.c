rts525a_switch_output_voltage(struct rtsx_pcr *pcr, u8 voltage)
{
	switch (voltage) {
	case OUTPUT_3V3:
		rtsx_pci_write_register(pcr, LDO_CONFIG2,
			LDO_D3318_MASK, LDO_D3318_33V);
		rtsx_pci_write_register(pcr, SD_PAD_CTL, SD_IO_USING_1V8, 0);
		break;
	case OUTPUT_1V8:
		rtsx_pci_write_register(pcr, LDO_CONFIG2,
			LDO_D3318_MASK, LDO_D3318_18V);
		rtsx_pci_write_register(pcr, SD_PAD_CTL, SD_IO_USING_1V8,
			SD_IO_USING_1V8);
		break;
	default:
		return -EINVAL;
	}

	rtsx_pci_init_cmd(pcr);
	rts5249_fill_driving(pcr, voltage);
	return rtsx_pci_send_cmd(pcr, 100);
}
