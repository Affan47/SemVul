countBlocks(bdescr *bd)
{
    W_ n;
    for (n=0; bd != NULL; bd=bd->link) {
	n += bd->blocks;
    }
    return n;
}
