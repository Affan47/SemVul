_edsf_persona_store_contacts_removed_cb (EdsfPersonaStore* self, GList* contacts_ids) {
	Block6Data* _data6_;
	GList* _tmp0_ = NULL;
	GeeLinkedList* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	_data6_ = g_slice_new0 (Block6Data);
	_data6_->_ref_count_ = 1;
	_data6_->self = g_object_ref (self);
	_tmp0_ = contacts_ids;
	_tmp1_ = _edsf_persona_store_copy_contacts_ids (self, _tmp0_);
	_data6_->copy = _tmp1_;
	_edsf_persona_store_idle_queue (self, ___lambda5__gsource_func, block6_data_ref (_data6_), block6_data_unref);
	block6_data_unref (_data6_);
	_data6_ = NULL;
}
