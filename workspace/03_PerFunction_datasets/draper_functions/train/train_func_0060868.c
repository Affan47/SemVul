playlist_positions_add_interval (playlist_positions_t *positions,
                                 gint start, gint end)
{
	GList *n;
	interval_t *ival, *prev_ival;


	if (start > end || start < 0) {
		return FALSE;
	}

	if (start == end) {
		playlist_positions_add_atom (positions, start);
		return TRUE;
	}


	prev_ival = NULL;
	for (n = positions->intervals; n; n = g_list_next (n)) {
		ival = (interval_t *) n->data;
		if (start > ival->end) {
			break;
		} else if (end < ival->start) {
			continue;
		} else {

			if (prev_ival) {
				ival->end = prev_ival->end;
				interval_free (prev_ival);
				positions->intervals = g_list_remove (positions->intervals,
				                                      prev_ival);
			}

			prev_ival = ival;
		}
	}

	if (prev_ival) {

		if (end > prev_ival->end) {
			prev_ival->end = end;
		}

		if (start < prev_ival->start) {
			prev_ival->start = start;
		}
	} else {

		positions->intervals = g_list_insert_before (positions->intervals, n,
		                                             interval_new (start, end));
	}


	for (n = positions->atoms; n; n = g_list_next (n)) {
		gint curr = GPOINTER_TO_INT (n->data);
		if (curr <= end) {
			if (curr >= start) {

				positions->atoms = g_list_delete_link (positions->atoms, n);
			} else {

				break;
			}
		}
	}

	return TRUE;
}
