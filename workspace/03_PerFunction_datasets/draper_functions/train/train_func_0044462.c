__lambda36_ (Block5Data* _data5_, void* ptr) {
	GType g_type;
	GBoxedCopyFunc g_dup_func;
	GDestroyNotify g_destroy_func;
	gconstpointer* gptr = NULL;
	void* _tmp0_ = NULL;
	gpointer obj = NULL;
	gconstpointer* _tmp1_ = NULL;
	g_type = _data5_->g_type;
	g_dup_func = _data5_->g_dup_func;
	g_destroy_func = _data5_->g_destroy_func;
	_tmp0_ = ptr;
	gptr = _tmp0_;
	_tmp1_ = gptr;
	gptr = NULL;
	obj = _tmp1_;
	_g_destroy_func0 (obj);
	obj = NULL;
	_g_destroy_func0 (obj);
}
