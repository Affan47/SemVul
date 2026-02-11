projects_get (Projects* self, gint id) {
	Project* result = NULL;
	gboolean _tmp0_ = FALSE;
	gint _tmp1_ = 0;
	GeeLinkedList* _tmp6_ = NULL;
	gint _tmp7_ = 0;
	gpointer _tmp8_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp1_ = id;
	if (_tmp1_ >= 0) {
		gint _tmp2_ = 0;
		GeeLinkedList* _tmp3_ = NULL;
		gint _tmp4_ = 0;
		gint _tmp5_ = 0;
		_tmp2_ = id;
		_tmp3_ = self->priv->projects;
		_tmp4_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp3_);
		_tmp5_ = _tmp4_;
		_tmp0_ = _tmp2_ < _tmp5_;
	} else {
		_tmp0_ = FALSE;
	}
	g_return_val_if_fail (_tmp0_, NULL);
	_tmp6_ = self->priv->projects;
	_tmp7_ = id;
	_tmp8_ = gee_abstract_list_get ((GeeAbstractList*) _tmp6_, _tmp7_);
	result = (Project*) _tmp8_;
	return result;
}
