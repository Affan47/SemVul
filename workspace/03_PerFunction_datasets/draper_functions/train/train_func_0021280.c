node_qrt_new(struct gnutella_node *n, struct routing_table *query_table)
{
	bool changed = FALSE;

	qrt_get_info(query_table, n->qrt_info);

	if (n->qrt_info->is_empty) {
		if (!NODE_HAS_EMPTY_QRT(n)) {
			n->flags |= NODE_F_EMPTY_QRT;
			changed = TRUE;
		}
	} else if (NODE_HAS_EMPTY_QRT(n)) {
		n->flags &= ~NODE_F_EMPTY_QRT;
		changed = TRUE;
	}

	return changed;
}
