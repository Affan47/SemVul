countops(struct btop *ops, int numops, block_t bloff, block_t maxbl)
{
    int i;

    for(i = 0; i < numops; i++) {
	if(ops[i].blk - bloff >= maxbl)
	    break;
    }
    return(i);
}
