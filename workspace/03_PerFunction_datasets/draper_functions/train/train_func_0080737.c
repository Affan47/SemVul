block2_data_unref (Block2Data* _data2_) {
	if ((--_data2_->_ref_count_) == 0) {
		_g_object_unref0 (_data2_->self);
		_g_object_unref0 (_data2_->acc);
		_g_object_unref0 (_data2_->edit_dialog);
		g_slice_free (Block2Data, _data2_);
	}
}
