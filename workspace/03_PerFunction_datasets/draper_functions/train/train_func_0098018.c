sdma_select_engine_vl(
	struct hfi1_devdata *dd,
	u32 selector,
	u8 vl)
{
	struct sdma_vl_map *m;
	struct sdma_map_elem *e;
	struct sdma_engine *rval;

	if (WARN_ON(vl > 8))
		return NULL;

	rcu_read_lock();
	m = rcu_dereference(dd->sdma_map);
	if (unlikely(!m)) {
		rcu_read_unlock();
		return NULL;
	}
	e = m->map[vl & m->mask];
	rval = e->sde[selector & e->mask];
	rcu_read_unlock();

	trace_hfi1_sdma_engine_select(dd, selector, vl, rval->this_idx);
	return rval;
}
