eth_calc_widths (ETableHeader *eth)
{
	gint i;
	gint extra;
	gdouble expansion;
	gint last_position = 0;
	gdouble next_position = 0;
	gint last_resizable = -1;
	gint *widths;
	gboolean changed;

	widths = g_new (int, eth->col_count);


	extra = eth->width - 1;
	expansion = 0;
	for (i = 0; i < eth->col_count; i++) {
		extra -= eth->columns[i]->min_width + eth->width_extras;
		if (eth->columns[i]->spec->resizable && eth->columns[i]->expansion > 0)
			last_resizable = i;
		expansion += eth->columns[i]->spec->resizable ? eth->columns[i]->expansion : 0;
		widths[i] = eth->columns[i]->min_width + eth->width_extras;
	}
	if (eth->sort_info)
		extra -= e_table_sort_info_grouping_get_count (eth->sort_info)
			* GROUP_INDENT;
	if (expansion != 0 && extra > 0) {
		for (i = 0; i < last_resizable; i++) {
			next_position +=
				extra * (eth->columns[i]->spec->resizable ?
				eth->columns[i]->expansion : 0) / expansion;
			widths[i] += next_position - last_position;
			last_position = next_position;
		}
		widths[i] += extra - last_position;
	}

	changed = FALSE;

	for (i = 0; i < eth->col_count; i++) {
		if (eth->columns[i]->width != widths[i]) {
			changed = TRUE;
			eth->columns[i]->width = widths[i];
		}
	}
	g_free (widths);
	if (changed)
		g_signal_emit (eth, eth_signals[DIMENSION_CHANGE], 0, eth->width);
	eth_update_offsets (eth);
}
