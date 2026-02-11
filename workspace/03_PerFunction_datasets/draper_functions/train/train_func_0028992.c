skk_context_remove_dictionary (SkkContext* self, SkkDict* dict) {
	GeeList* _tmp0_;
	SkkDict* _tmp1_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (dict != NULL);
	_tmp0_ = self->priv->_dictionaries;
	_tmp1_ = dict;
	gee_collection_remove ((GeeCollection*) _tmp0_, _tmp1_);
}
