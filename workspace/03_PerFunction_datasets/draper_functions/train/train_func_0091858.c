get_prefetch_info(Module_table *md_head, Pf_offset_type type, int cost)
{
    Module_table *mpt;
    Block *bpt;

    pf_offset_type = type;
    prefetch_cost = cost;
    for (mpt = md_head; mpt != NULL; mpt = mpt->next) {
        bpt = mpt->block_head;
        seek_loop(bpt->inner);
    }
}
