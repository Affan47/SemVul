add_call_module_block(Block *block_head, IntSet funcset, IntSet subrset,
                      const int level)
{
    Block *b;

    for (b = block_head; b != NULL; b = b->next) {
        if (b->cmp_localize != NULL
            && b->cmp_localize->memory_level == level) {
            add_call_module_set(b, funcset, subrset, level);
        } else if (b->inner != NULL) {
            add_call_module_block(b->inner, funcset, subrset, level);
        }
    }
}
