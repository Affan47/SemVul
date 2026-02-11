insertBlock(blocklist_t * bl, block_t * bp)
{
    if (bl->first) {
	bp->next = bl->first;
	bl->first = bp;
    } else {
	bl->first = bp;
	bl->last = bp;
    }
}
