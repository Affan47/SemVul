build_view_jump_to_file_lines (BuildView* self, GFile* file, gint start_line, gint end_line) {
	gboolean _tmp0_ = FALSE;
	gint _tmp1_ = 0;
	MainWindow* _tmp3_ = NULL;
	GFile* _tmp4_ = NULL;
	gint _tmp5_ = 0;
	gint _tmp6_ = 0;
	g_return_if_fail (self != NULL);
	g_return_if_fail (file != NULL);
	_tmp1_ = start_line;
	if (_tmp1_ >= 1) {
		gint _tmp2_ = 0;
		_tmp2_ = end_line;
		_tmp0_ = _tmp2_ >= 1;
	} else {
		_tmp0_ = FALSE;
	}
	g_return_if_fail (_tmp0_);
	_tmp3_ = self->priv->_main_window;
	_tmp4_ = file;
	_tmp5_ = start_line;
	_tmp6_ = end_line;
	main_window_jump_to_file_position (_tmp3_, _tmp4_, _tmp5_ - 1, _tmp6_ - 1);
}
