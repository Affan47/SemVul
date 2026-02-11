gee_abstract_map_real_foreach (GeeAbstractMap* self, GeeForallFunc f, void* f_target) {
	gboolean result = FALSE;
	GeeIterator* _tmp0_ = NULL;
	GeeIterator* _tmp1_ = NULL;
	GeeForallFunc _tmp2_ = NULL;
	void* _tmp2__target = NULL;
	gboolean _tmp3_ = FALSE;
	gboolean _tmp4_ = FALSE;
	_tmp0_ = gee_iterable_iterator ((GeeIterable*) self);
	_tmp1_ = _tmp0_;
	_tmp2_ = f;
	_tmp2__target = f_target;
	_tmp3_ = gee_traversable_foreach ((GeeTraversable*) _tmp1_, _tmp2_, _tmp2__target);
	_tmp4_ = _tmp3_;
	_g_object_unref0 (_tmp1_);
	result = _tmp4_;
	return result;
}
