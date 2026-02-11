_folks_individual_aggregator_is_primary_store_changed_cb (FolksIndividualAggregator* self, GObject* object, GParamSpec* pspec) {
	FolksPersonaStore* store = NULL;
	GObject* _tmp0_ = NULL;
	FolksPersonaStore* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp3_ = FALSE;
	FolksPersonaStore* _tmp4_ = NULL;
	gboolean _tmp5_ = FALSE;
	gboolean _tmp6_ = FALSE;
	gboolean _tmp9_ = FALSE;
	gboolean _tmp17_ = FALSE;
	g_return_if_fail (self != NULL);
	g_return_if_fail (object != NULL);
	g_return_if_fail (pspec != NULL);
	_tmp0_ = object;
	_tmp1_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp0_, FOLKS_TYPE_PERSONA_STORE, FolksPersonaStore));
	store = _tmp1_;
	_tmp4_ = store;
	_tmp5_ = folks_persona_store_get_is_primary_store (_tmp4_);
	_tmp6_ = _tmp5_;
	if (_tmp6_ == TRUE) {
		FolksPersonaStore* _tmp7_ = NULL;
		FolksPersonaStore* _tmp8_ = NULL;
		_tmp7_ = store;
		_tmp8_ = self->priv->_primary_store;
		_tmp3_ = _tmp7_ == _tmp8_;
	} else {
		_tmp3_ = FALSE;
	}
	_tmp9_ = _tmp3_;
	if (_tmp9_) {
		_tmp2_ = TRUE;
	} else {
		gboolean _tmp10_ = FALSE;
		FolksPersonaStore* _tmp11_ = NULL;
		gboolean _tmp12_ = FALSE;
		gboolean _tmp13_ = FALSE;
		gboolean _tmp16_ = FALSE;
		_tmp11_ = store;
		_tmp12_ = folks_persona_store_get_is_primary_store (_tmp11_);
		_tmp13_ = _tmp12_;
		if (_tmp13_ == FALSE) {
			FolksPersonaStore* _tmp14_ = NULL;
			FolksPersonaStore* _tmp15_ = NULL;
			_tmp14_ = store;
			_tmp15_ = self->priv->_primary_store;
			_tmp10_ = _tmp14_ != _tmp15_;
		} else {
			_tmp10_ = FALSE;
		}
		_tmp16_ = _tmp10_;
		_tmp2_ = _tmp16_;
	}
	_tmp17_ = _tmp2_;
	_vala_assert (_tmp17_, "(store.is_primary_store == true &&               store == this._primary_store) ||           (store.is_primary_store == false &&               store != this._primary_store)");
	_g_object_unref0 (store);
}
