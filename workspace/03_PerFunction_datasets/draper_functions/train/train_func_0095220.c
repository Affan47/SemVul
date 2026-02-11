DIM_InitSync(struct dim_channel *ch, u8 is_tx, u16 ch_address,
		u16 bytes_per_frame)
{
	if (!g.dim_is_initialized || !ch)
		return DIM_ERR_DRIVER_NOT_INITIALIZED;

	if (!check_channel_address(ch_address))
		return DIM_INIT_ERR_CHANNEL_ADDRESS;

	if (!check_bytes_per_frame(bytes_per_frame))
		return DIM_ERR_BAD_CONFIG;

	ch->dbr_size = bytes_per_frame * SYNC_DBR_FACTOR;
	ch->dbr_addr = alloc_dbr(ch->dbr_size);
	if (ch->dbr_addr >= DBR_SIZE)
		return DIM_INIT_ERR_OUT_OF_MEMORY;

	sync_init(ch, ch_address / 2, bytes_per_frame);

	dim2_configure_channel(ch->addr, CAT_CT_VAL_SYNC, is_tx,
			       ch->dbr_addr, ch->dbr_size, 0, true);

	return DIM_NO_ERROR;
}
