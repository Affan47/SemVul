search_is_frozen(gnet_search_t sh)
{
    search_ctrl_t *sch = search_find_by_handle(sh);

	search_ctrl_check(sch);

    return sbool_get(sch->frozen);
}
