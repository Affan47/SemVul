efx_farch_filter_table_remove(struct efx_nic *efx)
{
	struct efx_farch_filter_state *state = efx->filter_state;
	enum efx_farch_filter_table_id table_id;

	for (table_id = 0; table_id < EFX_FARCH_FILTER_TABLE_COUNT; table_id++) {
		kfree(state->table[table_id].used_bitmap);
		vfree(state->table[table_id].spec);
	}
	kfree(state);
}
