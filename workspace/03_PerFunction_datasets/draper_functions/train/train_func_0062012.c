fm_file_action_menu_match (FmFileActionMenu* self, GList* files) {
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_;
	gboolean _tmp3_;
	FmFileActionCondition* _tmp4_;
	GList* _tmp5_;
	gboolean _tmp6_ = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp1_ = ((FmFileActionObject*) self)->hidden;
	if (_tmp1_) {
		_tmp0_ = TRUE;
	} else {
		gboolean _tmp2_;
		_tmp2_ = ((FmFileActionObject*) self)->enabled;
		_tmp0_ = !_tmp2_;
	}
	_tmp3_ = _tmp0_;
	if (_tmp3_) {
		result = FALSE;
		return result;
	}
	_tmp4_ = ((FmFileActionObject*) self)->condition;
	_tmp5_ = files;
	_tmp6_ = fm_file_action_condition_match (_tmp4_, _tmp5_);
	if (!_tmp6_) {
		result = FALSE;
		return result;
	}
	result = TRUE;
	return result;
}
