projects_conflict (Projects* self, GFile* dir1, GFile* dir2) {
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_ = FALSE;
	GFile* _tmp2_ = NULL;
	GFile* _tmp3_ = NULL;
	gboolean _tmp4_ = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (dir1 != NULL, FALSE);
	g_return_val_if_fail (dir2 != NULL, FALSE);
	_tmp2_ = dir1;
	_tmp3_ = dir2;
	_tmp4_ = g_file_has_prefix (_tmp2_, _tmp3_);
	if (_tmp4_) {
		_tmp1_ = TRUE;
	} else {
		GFile* _tmp5_ = NULL;
		GFile* _tmp6_ = NULL;
		gboolean _tmp7_ = FALSE;
		_tmp5_ = dir2;
		_tmp6_ = dir1;
		_tmp7_ = g_file_has_prefix (_tmp5_, _tmp6_);
		_tmp1_ = _tmp7_;
	}
	if (_tmp1_) {
		_tmp0_ = TRUE;
	} else {
		GFile* _tmp8_ = NULL;
		GFile* _tmp9_ = NULL;
		gboolean _tmp10_ = FALSE;
		_tmp8_ = dir1;
		_tmp9_ = dir2;
		_tmp10_ = g_file_equal (_tmp8_, _tmp9_);
		_tmp0_ = _tmp10_;
	}
	result = _tmp0_;
	return result;
}
