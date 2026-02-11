personal_build_tools_move_down (PersonalBuildTools* self, gint tool_num) {
	gboolean _tmp0_ = FALSE;
	gint _tmp1_ = 0;
	gint _tmp6_ = 0;
	gint _tmp7_ = 0;
	g_return_if_fail (self != NULL);
	_tmp1_ = tool_num;
	if (0 <= _tmp1_) {
		gint _tmp2_ = 0;
		GeeLinkedList* _tmp3_ = NULL;
		gint _tmp4_ = 0;
		gint _tmp5_ = 0;
		_tmp2_ = tool_num;
		_tmp3_ = ((BuildTools*) self)->_build_tools;
		_tmp4_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp3_);
		_tmp5_ = _tmp4_;
		_tmp0_ = _tmp2_ < (_tmp5_ - 1);
	} else {
		_tmp0_ = FALSE;
	}
	g_return_if_fail (_tmp0_);
	_tmp6_ = tool_num;
	_tmp7_ = tool_num;
	personal_build_tools_swap (self, _tmp6_, _tmp7_ + 1);
}
