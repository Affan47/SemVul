fm_file_action_item_new_for_action_object (FmFileActionObject* action_obj, GList* files) {
	FmFileActionItem* result = NULL;
	FmFileActionItem* item;
	FmFileActionObject* _tmp0_;
	FmFileActionType _tmp1_;
	g_return_val_if_fail (action_obj != NULL, NULL);
	item = NULL;
	_tmp0_ = action_obj;
	_tmp1_ = _tmp0_->type;
	if (_tmp1_ == FM_FILE_ACTION_TYPE_MENU) {
		FmFileActionObject* _tmp2_;
		FmFileActionMenu* _tmp3_;
		FmFileActionMenu* menu;
		FmFileActionMenu* _tmp4_;
		GList* _tmp5_;
		gboolean _tmp6_ = FALSE;
		_tmp2_ = action_obj;
		_tmp3_ = _g_object_ref0 (FM_FILE_ACTION_MENU (_tmp2_));
		menu = _tmp3_;
		_tmp4_ = menu;
		_tmp5_ = files;
		_tmp6_ = fm_file_action_menu_match (_tmp4_, _tmp5_);
		if (_tmp6_) {
			FmFileActionMenu* _tmp7_;
			GList* _tmp8_;
			FmFileActionItem* _tmp9_;
			FmFileActionItem* _tmp10_;
			GList* _tmp11_;
			_tmp7_ = menu;
			_tmp8_ = files;
			_tmp9_ = fm_file_action_item_new_from_menu (_tmp7_, _tmp8_);
			_fm_file_action_item_unref0 (item);
			item = _tmp9_;
			_tmp10_ = item;
			_tmp11_ = _tmp10_->children;
			if (_tmp11_ == NULL) {
				_fm_file_action_item_unref0 (item);
				item = NULL;
			}
		}
		_g_object_unref0 (menu);
	} else {
		FmFileActionObject* _tmp12_;
		FmFileAction* _tmp13_;
		FmFileAction* action;
		FmFileActionProfile* profile = NULL;
		FmFileAction* _tmp14_;
		GList* _tmp15_;
		FmFileActionProfile* _tmp16_ = NULL;
		gboolean _tmp17_ = FALSE;
		_tmp12_ = action_obj;
		_tmp13_ = _g_object_ref0 (FM_FILE_ACTION (_tmp12_));
		action = _tmp13_;
		_tmp14_ = action;
		_tmp15_ = files;
		_tmp17_ = fm_file_action_match (_tmp14_, _tmp15_, &_tmp16_);
		profile = _tmp16_;
		if (_tmp17_) {
			FmFileAction* _tmp18_;
			FmFileActionProfile* _tmp19_;
			GList* _tmp20_;
			FmFileActionItem* _tmp21_;
			_tmp18_ = action;
			_tmp19_ = profile;
			_tmp20_ = files;
			_tmp21_ = fm_file_action_item_new_from_action (_tmp18_, _tmp19_, _tmp20_);
			_fm_file_action_item_unref0 (item);
			item = _tmp21_;
		}
		_g_object_unref0 (action);
	}
	result = item;
	return result;
}
