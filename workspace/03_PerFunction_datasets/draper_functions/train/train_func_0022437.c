node_remove_worst(bool non_local)
{
    GSList *sl;
    GSList *m = NULL;
    struct gnutella_node *n;
    int worst = 0, score, num = 0;


    for (sl = sl_nodes; sl; sl = g_slist_next(sl)) {
        n = sl->data;
        if (n->status != GTA_NODE_CONNECTED)
            continue;


        if (!non_local && whitelist_check(n->addr))
            continue;


		if (non_local && host_is_nearby(n->addr))
			continue;

        score = n->n_weird * 100 + n->n_bad * 10 + n->n_dups;

        if (score > worst) {
            worst = score;
            num = 0;
			gm_slist_free_null(&m);
        }
        if (score == worst) {
            m = g_slist_prepend(m, n);
            num++;
        }
    }
    if (m) {
		m = g_slist_reverse(m);
        n = g_slist_nth_data(m, random_value(num - 1));
        g_slist_free(m);
		if (non_local)
			node_bye_if_writable(n, 202, "Local Node Preferred");
		else {
			node_bye_if_writable(n, 202, "Making Room for Another Node");
		}
        return TRUE;
    }

    return FALSE;
}
