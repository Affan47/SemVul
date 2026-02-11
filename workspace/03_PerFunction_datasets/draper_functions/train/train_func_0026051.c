folks_individual_real_change_avatar_data_free (gpointer _data) {
	FolksIndividualChangeAvatarData* _data_;
	_data_ = _data;
	_g_object_unref0 (_data_->avatar);
	_g_object_unref0 (_data_->self);
	g_slice_free (FolksIndividualChangeAvatarData, _data_);
}
