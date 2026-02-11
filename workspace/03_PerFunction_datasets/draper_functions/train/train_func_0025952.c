qlcnic_83xx_flash_write32(struct qlcnic_adapter *adapter, u32 addr,
			      u32 *p_data)
{
	int ret = -EIO;
	u32 addr1 = 0x00800000 | (addr >> 2);

	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR, addr1);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_WRDATA, *p_data);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_CONTROL,
				     QLC_83XX_FLASH_LAST_ERASE_MS_VAL);
	ret = qlcnic_83xx_poll_flash_status_reg(adapter);
	if (ret) {
		dev_err(&adapter->pdev->dev,
			"%s: failed at %d\n", __func__, __LINE__);
		return -EIO;
	}

	return 0;
}
