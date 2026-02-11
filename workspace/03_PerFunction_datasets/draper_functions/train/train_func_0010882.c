bsched_add_stealer(bsched_bws_t bws, bsched_bws_t bws_stealer)
{
	bsched_t *bs, *stealer;

	g_assert(bws != bws_stealer);

	bs = bsched_get(bws);
	stealer = bsched_get(bws_stealer);
	g_assert((bs->flags & BS_F_RW) == (stealer->flags & BS_F_RW));

	bs->stealers = g_slist_prepend(bs->stealers, stealer);
}
