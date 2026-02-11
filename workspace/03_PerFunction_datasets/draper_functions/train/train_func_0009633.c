search_query(gnet_search_t sh)
{
    search_ctrl_t *sch = search_find_by_handle(sh);

	search_ctrl_check(sch);
    g_assert(sch->name != NULL);

    return sch->name;
}
