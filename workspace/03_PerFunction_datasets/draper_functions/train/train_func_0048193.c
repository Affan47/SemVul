qlcnic_83xx_read_flash_mfg_id(struct qlcnic_adapter *adapter)
{
	int ret, err = 0;
	u32 mfg_id;

	if (qlcnic_83xx_lock_flash(adapter))
		return -EIO;

	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR,
				     QLC_83XX_FLASH_FDT_READ_MFG_ID_VAL);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_CONTROL,
				     QLC_83XX_FLASH_READ_CTRL);
	ret = qlcnic_83xx_poll_flash_status_reg(adapter);
	if (ret) {
		qlcnic_83xx_unlock_flash(adapter);
		return -EIO;
	}

	mfg_id = QLCRD32(adapter, QLC_83XX_FLASH_RDDATA, &err);
	if (err == -EIO) {
		qlcnic_83xx_unlock_flash(adapter);
		return err;
	}

	adapter->flash_mfg_id = (mfg_id & 0xFF);
	qlcnic_83xx_unlock_flash(adapter);

	return 0;
}
