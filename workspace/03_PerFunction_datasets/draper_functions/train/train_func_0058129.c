ath6kl_set_addrwin_reg(struct ath6kl *ar, u32 reg_addr, u32 addr)
{
	int status;
	u8 addr_val[4];
	s32 i;


	for (i = 1; i <= 3; i++) {


		memset(addr_val, ((u8 *)&addr)[i], 4);


		status = ath6kl_sdio_read_write_sync(ar, reg_addr + i, addr_val,
					     4, HIF_WR_SYNC_BYTE_FIX);
		if (status)
			break;
	}

	if (status) {
		ath6kl_err("%s: failed to write initial bytes of 0x%x to window reg: 0x%X\n",
			   __func__, addr, reg_addr);
		return status;
	}


	status = ath6kl_sdio_read_write_sync(ar, reg_addr, (u8 *)(&addr),
				     4, HIF_WR_SYNC_BYTE_INC);

	if (status) {
		ath6kl_err("%s: failed to write 0x%x to window reg: 0x%X\n",
			   __func__, addr, reg_addr);
		return status;
	}

	return 0;
}
