search_start(gnet_search_t sh)
{
    search_ctrl_t *sch = search_find_by_handle(sh);

	search_ctrl_check(sch);
    g_assert(sbool_get(sch->frozen));

    sch->frozen = sbool_set(FALSE);

    if (sbool_get(sch->active)) {
		search_reissue(sch);
	}
	search_status_changed(sh);
}
