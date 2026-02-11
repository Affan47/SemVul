search_target_mtg_of_alg_set(Block *block)
{
    Block *b, *b2 = NULL;

    for (b = block; b != NULL; b = b->inner) {
        if ((!is_outer_loop_tlg(b->outer))
            || (is_do_loop(b) && b->next == NULL)) {
            b2 = b->inner;
        }
    }

    return b2;
}
