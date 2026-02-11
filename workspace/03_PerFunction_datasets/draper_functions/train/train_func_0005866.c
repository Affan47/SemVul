link_prev_and_numbering_Block(Block *bp)
{
    int     no=0;
    while (bp) {
        bp->no = ++no;
        bp->usage = USE_BLOCK;
        if (bp->next)   bp->next->prev=bp;
        if (bp->inner)  link_prev_and_numbering_Block(bp->inner);
        bp = bp->next;
    }
    return  no;
}
