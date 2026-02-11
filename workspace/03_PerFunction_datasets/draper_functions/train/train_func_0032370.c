e_table_header_move (ETableHeader *eth,
                     gint source_index,
                     gint target_index)
{
	ETableCol *old;

	g_return_if_fail (eth != NULL);
	g_return_if_fail (E_IS_TABLE_HEADER (eth));
	g_return_if_fail (source_index >= 0);
	g_return_if_fail (target_index >= 0);
	g_return_if_fail (source_index < eth->col_count);


	g_return_if_fail (target_index < eth->col_count + 1);

	if (source_index < target_index)
		target_index--;

	old = eth->columns[source_index];
	eth_do_remove (eth, source_index, FALSE);
	eth_do_insert (eth, target_index, old);
	eth_update_offsets (eth);

	g_signal_emit (eth, eth_signals[DIMENSION_CHANGE], 0, eth->width);
	g_signal_emit (eth, eth_signals[STRUCTURE_CHANGE], 0);
}
