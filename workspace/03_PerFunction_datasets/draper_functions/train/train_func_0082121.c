set_blkptr_array(Block *block, Block ***bpary, int *num)
{
    int i;

    if (!*bpary)
        *bpary = (Block **)malloc(sizeof(Block *));
    else {
        for (i=0 ; i<*num ; i++)
            if ((*bpary)[i]==block)
                return;

        if (!(*num & (*num-1)))
            *bpary = (Block **)realloc(*bpary, sizeof(Block *)*(*num)*2);
    }
    (*bpary)[*num]=block;
    (*num)++;
}
