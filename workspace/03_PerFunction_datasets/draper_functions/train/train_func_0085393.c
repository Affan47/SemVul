block_insert_inner_tail0(Block *outer, Block *block, Boolean flg_expand)
{
    Boolean flg_connect_void_block = FALSE;

    if (block->kind == BLOCK && flg_expand) {
        Block *b, *next;
        b = block->inner;
        while (b != NULL) {
            next = b->next;
            unlink_block(b);
            if (flg_connect_void_block || !block_is_void(b))
                block_insert_inner_tail(outer, b);
            b = next;
        }
    } else {
        if (flg_connect_void_block || !block_is_void(block))
            block_insert_inner_tail(outer, block);
    }
}
