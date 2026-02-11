__lambda8_ (Block10Data* _data10_, gpointer item) {
	GeeTraversable * self;
	GType a_type;
	GBoxedCopyFunc a_dup_func;
	GDestroyNotify a_destroy_func;
	gboolean result = FALSE;
	GeeFoldFunc _tmp0_ = NULL;
	void* _tmp0__target = NULL;
	gpointer _tmp1_ = NULL;
	gpointer _tmp2_ = NULL;
	gpointer _tmp3_ = NULL;
	self = _data10_->self;
	a_type = _data10_->a_type;
	a_dup_func = _data10_->a_dup_func;
	a_destroy_func = _data10_->a_destroy_func;
	_tmp0_ = _data10_->f;
	_tmp0__target = _data10_->f_target;
	_tmp1_ = item;
	item = NULL;
	_tmp2_ = _data10_->seed;
	_data10_->seed = NULL;
	_tmp3_ = _tmp0_ (_tmp1_, _tmp2_, _tmp0__target);
	_a_destroy_func0 (_data10_->seed);
	_data10_->seed = _tmp3_;
	result = TRUE;
	((item == NULL) || (GEE_TRAVERSABLE_GET_INTERFACE (self)->get_g_destroy_func (self) == NULL)) ? NULL : (item = (GEE_TRAVERSABLE_GET_INTERFACE (self)->get_g_destroy_func (self) (item), NULL));
	return result;
}
