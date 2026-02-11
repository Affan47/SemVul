directory_compare_directories (Directory* a, Directory* b) {
	gint result = 0;
	GCompareFunc _tmp0_;
	Directory* _tmp1_;
	const gchar* _tmp2_;
	Directory* _tmp3_;
	const gchar* _tmp4_;
	gint _tmp5_ = 0;
	g_return_val_if_fail (a != NULL, 0);
	g_return_val_if_fail (b != NULL, 0);
	_tmp0_ = g_strcmp0;
	_tmp1_ = a;
	_tmp2_ = _tmp1_->name;
	_tmp3_ = b;
	_tmp4_ = _tmp3_->name;
	_tmp5_ = _tmp0_ (_tmp2_, _tmp4_);
	result = _tmp5_;
	return result;
}
