mark_used_label_block(IntSet set, Block *block)
{
    Block *b;

    if (block->pre_head != NULL)
        mark_used_label_pestm(set, block->pre_head);

    for (b = block->inner; b != NULL; b = b->next)
        mark_used_label_block(set, b);

    if (block->post_head != NULL)
        mark_used_label_pestm(set, block->post_head);
}
