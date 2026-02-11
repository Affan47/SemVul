idbm_bind_iface_to_nodes(idbm_disc_nodes_fn *disc_node_fn,
				    void *data, struct iface_rec *iface,
				    struct list_head *bound_recs)
{
	struct node_rec *rec, *tmp;
	struct list_head new_recs;
	int rc;

	INIT_LIST_HEAD(&new_recs);
	rc = disc_node_fn(data, iface, &new_recs);
	if (rc)
		return rc;

	list_for_each_entry_safe(rec, tmp, &new_recs, list) {
		list_del_init(&rec->list);
		list_add_tail(&rec->list, bound_recs);
		iface_copy(&rec->iface, iface);
	}
	return 0;
}
