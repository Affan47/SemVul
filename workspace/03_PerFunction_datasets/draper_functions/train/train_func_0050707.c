new_IteratorG(CTX ctx, kclass_t cid, kObject *source, knh_Fitrnext fnext)
{
	DBG_ASSERT(C_bcid(cid) == CLASS_Iterator);
	kIterator *it = new_O(Iterator, cid);
	if(IS_NULL(source)) fnext = Fitrnext_end;
	KNH_SETv_withWB(ctx, it, DP(it)->source, source);
	it->fnext_1 = fnext;
	return it;
}
