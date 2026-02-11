dht_overlap_calc (dht_layout_t *old, int o, dht_layout_t *new, int n)
{
	if (o >= old->cnt || n >= new->cnt)
		return 0;

	if (old->list[o].err > 0 || new->list[n].err > 0)
		return 0;

        if (old->list[o].start == old->list[o].stop) {
                return 0;
        }

        if (new->list[n].start == new->list[n].stop) {
                return 0;
        }

	if ((old->list[o].start > new->list[n].stop) ||
	    (old->list[o].stop < new->list[n].start))
		return 0;

	return min (old->list[o].stop, new->list[n].stop) -
	        max (old->list[o].start, new->list[n].start) + 1;
}
