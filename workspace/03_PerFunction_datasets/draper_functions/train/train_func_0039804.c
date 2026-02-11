__lambda2_ (Block6Data* _data6_) {
	GType g_type;
	GBoxedCopyFunc g_dup_func;
	GDestroyNotify g_destroy_func;
	GeeLazy* result = NULL;
	g_type = _data6_->g_type;
	g_dup_func = _data6_->g_dup_func;
	g_destroy_func = _data6_->g_destroy_func;
	while (TRUE) {
		GeeIterator* _tmp0_ = NULL;
		_tmp0_ = _data6_->current;
		if (_tmp0_ == NULL) {
			GeeIterator* _tmp1_ = NULL;
			gboolean _tmp2_ = FALSE;
			_tmp1_ = _data6_->iters;
			_tmp2_ = gee_iterator_next (_tmp1_);
			if (_tmp2_) {
				GeeIterator* _tmp3_ = NULL;
				gpointer _tmp4_ = NULL;
				_tmp3_ = _data6_->iters;
				_tmp4_ = gee_iterator_get (_tmp3_);
				_g_object_unref0 (_data6_->current);
				_data6_->current = (GeeIterator*) _tmp4_;
			} else {
				result = NULL;
				return result;
			}
		} else {
			GeeIterator* _tmp5_ = NULL;
			gboolean _tmp6_ = FALSE;
			_tmp5_ = _data6_->current;
			_tmp6_ = gee_iterator_next (_tmp5_);
			if (_tmp6_) {
				GeeIterator* _tmp7_ = NULL;
				gpointer _tmp8_ = NULL;
				gpointer _tmp9_ = NULL;
				GeeLazy* _tmp10_ = NULL;
				GeeLazy* _tmp11_ = NULL;
				_tmp7_ = _data6_->current;
				_tmp8_ = gee_iterator_get (_tmp7_);
				_tmp9_ = _tmp8_;
				_tmp10_ = gee_lazy_new_from_value (g_type, (GBoxedCopyFunc) g_dup_func, g_destroy_func, _tmp9_);
				_tmp11_ = _tmp10_;
				_g_destroy_func0 (_tmp9_);
				result = _tmp11_;
				return result;
			} else {
				_g_object_unref0 (_data6_->current);
				_data6_->current = NULL;
			}
		}
	}
}
