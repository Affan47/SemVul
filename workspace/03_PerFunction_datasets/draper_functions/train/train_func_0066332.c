latex_post_processor_file_exists (LatexPostProcessor* self, const gchar* filename) {
	gboolean result = FALSE;
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	gboolean _tmp3_ = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (filename != NULL, FALSE);
	_tmp0_ = filename;
	_tmp1_ = latex_post_processor_get_path_if_file_exists (self, _tmp0_);
	_tmp2_ = _tmp1_;
	_tmp3_ = _tmp2_ != NULL;
	_g_free0 (_tmp2_);
	result = _tmp3_;
	return result;
}
