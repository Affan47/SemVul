search_dissociate_browse(gnet_search_t search_handle, struct download *d)
{
    search_ctrl_t *sch = search_find_by_handle(search_handle);

	search_ctrl_check(sch);
	g_assert(sbool_get(sch->browse));
	g_assert(sch->download == d);

	sch->download = NULL;
	if (!sbool_get(sch->frozen)) {
		search_stop(sch->search_handle);
		search_status_changed(sch->search_handle);
	}
}
