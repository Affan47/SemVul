get_max_tlg_tag(Block *block_head)
{
    Block *b;
    int max = 0;

    for (b = block_head; b != NULL; b = b->next) {
        if (block_has_tlg_tag(b) && max < b->tlg_tag) {
            max = b->tlg_tag;
        }
    }

    return max;
}
