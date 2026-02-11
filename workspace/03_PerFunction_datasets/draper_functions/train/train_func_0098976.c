contacts_row_group_add (ContactsRowGroup* self, ContactsRow* row) {
	Block34Data* _data34_;
	ContactsRow* _tmp0_ = NULL;
	ContactsRow* _tmp1_ = NULL;
	GeeArrayList* _tmp2_ = NULL;
	ContactsRow* _tmp3_ = NULL;
	ContactsRow* _tmp4_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (row != NULL);
	_data34_ = g_slice_new0 (Block34Data);
	_data34_->_ref_count_ = 1;
	_data34_->self = g_object_ref (self);
	_tmp0_ = row;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (_data34_->row);
	_data34_->row = _tmp1_;
	_tmp2_ = self->priv->rows;
	_tmp3_ = _data34_->row;
	gee_abstract_collection_add ((GeeAbstractCollection*) _tmp2_, _tmp3_);
	_tmp4_ = _data34_->row;
	g_signal_connect_data ((GtkWidget*) _tmp4_, "destroy", (GCallback) ___lambda134__gtk_widget_destroy, block34_data_ref (_data34_), (GClosureNotify) block34_data_unref, 0);
	block34_data_unref (_data34_);
	_data34_ = NULL;
}
