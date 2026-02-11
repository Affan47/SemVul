get_stack(const E_Border *bd)
{
    int i;
    for (i = 0; i < TILING_MAX_STACKS; i++) {
        if (EINA_LIST_IS_IN(_G.tinfo->stacks[i], bd))
            return i;
    }
    return -1;
}
