qlcnic_83xx_disable_flash_write(struct qlcnic_adapter *adapter)
{
	int ret;

	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR,
				     (QLC_83XX_FLASH_FDT_WRITE_DEF_SIG |
				     adapter->ahw->fdt.write_statusreg_cmd));
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_WRDATA,
				     adapter->ahw->fdt.write_disable_bits);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_CONTROL,
				     QLC_83XX_FLASH_SECOND_ERASE_MS_VAL);
	ret = qlcnic_83xx_poll_flash_status_reg(adapter);
	if (ret)
		return -EIO;

	return 0;
}
