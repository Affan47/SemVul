brb_next(struct bop_ring_buffer *brb, unsigned old)
{
	unsigned r = old + 1;
	return (r >= (sizeof(brb->bops) / sizeof(*brb->bops))) ? 0 : r;
}
