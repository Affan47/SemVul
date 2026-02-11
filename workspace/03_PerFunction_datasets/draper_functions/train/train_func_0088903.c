efx_farch_filter_rfs_expire_one(struct efx_nic *efx, u32 flow_id,
				     unsigned int index)
{
	struct efx_farch_filter_state *state = efx->filter_state;
	struct efx_farch_filter_table *table =
		&state->table[EFX_FARCH_FILTER_TABLE_RX_IP];

	if (test_bit(index, table->used_bitmap) &&
	    table->spec[index].priority == EFX_FILTER_PRI_HINT &&
	    rps_may_expire_flow(efx->net_dev, table->spec[index].dmaq_id,
				flow_id, index)) {
		efx_farch_filter_table_clear_entry(efx, table, index);
		return true;
	}

	return false;
}
