rsi_copy_to_card(struct rsi_common *common,
			    const u8 *fw,
			    u32 len,
			    u32 num_blocks)
{
	struct rsi_hw *adapter = common->priv;
	struct rsi_91x_sdiodev *dev =
		(struct rsi_91x_sdiodev *)adapter->rsi_dev;
	u32 indx, ii;
	u32 block_size = dev->tx_blk_size;
	u32 lsb_address;
	__le32 data[] = { TA_HOLD_THREAD_VALUE, TA_SOFT_RST_CLR,
			  TA_PC_ZERO, TA_RELEASE_THREAD_VALUE };
	u32 address[] = { TA_HOLD_THREAD_REG, TA_SOFT_RESET_REG,
			  TA_TH0_PC_REG, TA_RELEASE_THREAD_REG };
	u32 base_address;
	u16 msb_address;

	base_address = TA_LOAD_ADDRESS;
	msb_address = base_address >> 16;

	for (indx = 0, ii = 0; ii < num_blocks; ii++, indx += block_size) {
		lsb_address = ((u16) base_address | RSI_SD_REQUEST_MASTER);
		if (rsi_sdio_write_register_multiple(adapter,
						     lsb_address,
						     (u8 *)(fw + indx),
						     block_size)) {
			rsi_dbg(ERR_ZONE,
				"%s: Unable to load %s blk\n", __func__,
				FIRMWARE_RSI9113);
			return -1;
		}
		rsi_dbg(INIT_ZONE, "%s: loading block: %d\n", __func__, ii);
		base_address += block_size;
		if ((base_address >> 16) != msb_address) {
			msb_address += 1;
			if (rsi_sdio_master_access_msword(adapter,
							  msb_address)) {
				rsi_dbg(ERR_ZONE,
					"%s: Unable to set ms word reg\n",
					__func__);
				return -1;
			}
		}
	}

	if (len % block_size) {
		lsb_address = ((u16) base_address | RSI_SD_REQUEST_MASTER);
		if (rsi_sdio_write_register_multiple(adapter,
						     lsb_address,
						     (u8 *)(fw + indx),
						     len % block_size)) {
			rsi_dbg(ERR_ZONE,
				"%s: Unable to load f/w\n", __func__);
			return -1;
		}
	}
	rsi_dbg(INIT_ZONE,
		"%s: Succesfully loaded TA instructions\n", __func__);

	if (rsi_sdio_master_access_msword(adapter, TA_BASE_ADDR)) {
		rsi_dbg(ERR_ZONE,
			"%s: Unable to set ms word to common reg\n",
			__func__);
		return -1;
	}

	for (ii = 0; ii < ARRAY_SIZE(data); ii++) {

		if (rsi_sdio_write_register_multiple(adapter,
						     (address[ii] |
						     RSI_SD_REQUEST_MASTER),
						     (u8 *)&data[ii],
						     4)) {
			rsi_dbg(ERR_ZONE,
				"%s: Unable to hold TA threads\n", __func__);
			return -1;
		}
	}

	rsi_dbg(INIT_ZONE, "%s: loaded firmware\n", __func__);
	return 0;
}
