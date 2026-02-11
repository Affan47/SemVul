mono_linterval_split (MonoCompile *cfg, MonoLiveInterval *interval, MonoLiveInterval **i1, MonoLiveInterval **i2, int pos)
{
	MonoLiveRange2 *r;

	g_assert (pos > interval->range->from && pos <= interval->last_range->to);

	*i1 = mono_mempool_alloc0 (cfg->mempool, sizeof (MonoLiveInterval));
	*i2 = mono_mempool_alloc0 (cfg->mempool, sizeof (MonoLiveInterval));

	for (r = interval->range; r; r = r->next) {
		if (pos > r->to) {

			mono_linterval_add_range (cfg, *i1, r->from, r->to);
		} else if (pos > r->from && pos <= r->to) {

			mono_linterval_add_range (cfg, *i1, r->from, pos - 1);
			mono_linterval_add_range (cfg, *i2, pos, r->to);
		} else {

			mono_linterval_add_range (cfg, *i2, r->from, r->to);
		}
	}
}
