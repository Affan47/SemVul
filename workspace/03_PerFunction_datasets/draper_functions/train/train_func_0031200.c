get_block_entry_latency(const Block *bpt, const int entry)
{
    Cmp_localize_group_info *g;
    Array_table *ltbl;

    if (bpt == NULL) {
        return csm_latency;
    }

    g = get_group_info_entry(bpt->cmp_localize, entry);
    ltbl = search_array_table(g->lhead, entry);
	return get_memory_latency(ltbl->kind);
}
