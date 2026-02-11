zeitgeist_engine_construct (GType object_type, GError** error) {
	ZeitgeistEngine * self = NULL;
	ZeitgeistSQLiteDatabase* _tmp0_ = NULL;
	ZeitgeistSQLiteDatabase* _tmp1_ = NULL;
	ZeitgeistSQLiteDatabase* _tmp2_ = NULL;
	guint32 _tmp3_ = 0U;
	ZeitgeistSQLiteDatabase* _tmp4_ = NULL;
	ZeitgeistSQLiteDatabase* _tmp5_ = NULL;
	guint32 _tmp6_ = 0U;
	ZeitgeistRegisterExtensionFunc* _tmp7_ = NULL;
	ZeitgeistRegisterExtensionFunc* _tmp8_ = NULL;
	gint _tmp8__length1 = 0;
	ZeitgeistExtensionCollection* _tmp9_ = NULL;
	GError * _inner_error_ = NULL;
	_tmp1_ = zeitgeist_sq_lite_database_new (&_inner_error_);
	_tmp0_ = _tmp1_;
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == ZEITGEIST_ENGINE_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	_tmp2_ = _tmp0_;
	self = (ZeitgeistEngine*) g_object_new (object_type, "database", _tmp2_, NULL);
	_g_object_unref0 (_tmp2_);
	_tmp4_ = zeitgeist_db_reader_get_database ((ZeitgeistDbReader*) self);
	_tmp5_ = _tmp4_;
	_tmp6_ = zeitgeist_sq_lite_database_get_last_id (_tmp5_, &_inner_error_);
	_tmp3_ = _tmp6_;
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == ZEITGEIST_ENGINE_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->priv->last_id = _tmp3_;
	_tmp7_ = g_new0 (ZeitgeistRegisterExtensionFunc, 0);
	_tmp8_ = _tmp7_;
	_tmp8__length1 = 0;
	_tmp9_ = zeitgeist_extension_collection_new (self, _tmp8_, 0);
	_g_object_unref0 (self->priv->extension_collection);
	self->priv->extension_collection = _tmp9_;
	_tmp8_ = (g_free (_tmp8_), NULL);
	return self;
}
