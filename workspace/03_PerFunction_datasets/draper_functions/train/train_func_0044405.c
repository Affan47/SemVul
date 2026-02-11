efx_farch_filter_table_clear(struct efx_nic *efx,
			     enum efx_farch_filter_table_id table_id,
			     enum efx_filter_priority priority)
{
	struct efx_farch_filter_state *state = efx->filter_state;
	struct efx_farch_filter_table *table = &state->table[table_id];
	unsigned int filter_idx;

	spin_lock_bh(&efx->filter_lock);
	for (filter_idx = 0; filter_idx < table->size; ++filter_idx) {
		if (table->spec[filter_idx].priority != EFX_FILTER_PRI_AUTO)
			efx_farch_filter_remove(efx, table,
						filter_idx, priority);
	}
	spin_unlock_bh(&efx->filter_lock);
}
