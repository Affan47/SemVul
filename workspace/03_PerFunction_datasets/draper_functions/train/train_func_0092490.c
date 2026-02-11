free_block_array_dependence_range_next(Block *block_head)
{
    Block *bpt;

    free_block_array_dependence_range_edge(block_head);

    for (bpt = block_head; bpt != NULL; bpt = bpt->next) {
        free_block_array_dependence_range_next(bpt->inner);
        free_block_array_dependence_range(bpt);
    }
}
