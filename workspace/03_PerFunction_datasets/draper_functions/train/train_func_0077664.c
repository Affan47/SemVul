tracker_history_finalize (TrackerHistory* obj) {
	TrackerHistory * self;
	GKeyFile* _tmp0_;
	gchar** _tmp1_;
	gint _tmp1__length1;
	GError * _inner_error_ = NULL;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TRACKER_TYPE_HISTORY, TrackerHistory);
	g_debug ("tracker-history.vala:62: Saving history");
	_tmp0_ = self->priv->data;
	_tmp1_ = self->priv->history;
	_tmp1__length1 = self->priv->history_length1;
	g_key_file_set_string_list (_tmp0_, "History", "criteria", (const gchar* const*) _tmp1_, _tmp1__length1);
	{
		GKeyFile* _tmp2_;
		gchar* _tmp3_ = NULL;
		gchar* output;
		const gchar* _tmp4_;
		const gchar* _tmp5_;
		_tmp2_ = self->priv->data;
		_tmp3_ = g_key_file_to_data (_tmp2_, NULL, NULL);
		output = _tmp3_;
		_tmp4_ = self->priv->filename;
		_tmp5_ = output;
		g_file_set_contents (_tmp4_, _tmp5_, (gssize) (-1), &_inner_error_);
		if (_inner_error_ != NULL) {
			_g_free0 (output);
			if (_inner_error_->domain == G_FILE_ERROR) {
				goto __catch0_g_file_error;
			}
			_g_free0 (output);
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
		}
		_g_free0 (output);
	}
	goto __finally0;
	__catch0_g_file_error:
	{
		GError* e1 = NULL;
		const gchar* _tmp6_;
		GError* _tmp7_;
		const gchar* _tmp8_;
		e1 = _inner_error_;
		_inner_error_ = NULL;
		_tmp6_ = self->priv->filename;
		_tmp7_ = e1;
		_tmp8_ = _tmp7_->message;
		g_warning ("tracker-history.vala:71: Could not save history to file:'%s': %s", _tmp6_, _tmp8_);
		_g_error_free0 (e1);
	}
	__finally0:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
	}
	g_debug ("tracker-history.vala:74:   Done");
	_g_key_file_free0 (self->priv->data);
	_g_free0 (self->priv->filename);
	self->priv->history = (_vala_array_free (self->priv->history, self->priv->history_length1, (GDestroyNotify) g_free), NULL);
}
