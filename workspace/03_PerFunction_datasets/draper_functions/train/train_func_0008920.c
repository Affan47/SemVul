add_array_dim_for_slot_blocks(Block *block_head)
{
    Block *b;

    for (b = block_head; b != NULL; b = b->next) {
        if (b->cmp_localize != NULL) {
            add_array_dim_for_slot_block(b);
        }
    }
}
