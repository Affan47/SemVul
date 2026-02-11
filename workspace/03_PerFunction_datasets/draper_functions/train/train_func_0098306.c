umockdev_script_runner_construct (GType object_type, const gchar* device, const gchar* script_file, gint fd, GError** error) {
	UMockdevScriptRunner* self = NULL;
	const gchar* _tmp0_ = NULL;
	FILE* _tmp1_ = NULL;
	FILE* _tmp2_ = NULL;
	const gchar* _tmp8_ = NULL;
	const gchar* _tmp9_ = NULL;
	gchar* _tmp10_ = NULL;
	gint _tmp11_ = 0;
	const gchar* _tmp12_ = NULL;
	GThread* _tmp13_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (device != NULL, NULL);
	g_return_val_if_fail (script_file != NULL, NULL);
	self = (UMockdevScriptRunner*) g_type_create_instance (object_type);
	_tmp0_ = script_file;
	_tmp1_ = g_fopen (_tmp0_, "r");
	_fclose0 (self->priv->script);
	self->priv->script = _tmp1_;
	_tmp2_ = self->priv->script;
	if (_tmp2_ == NULL) {
		const gchar* _tmp3_ = NULL;
		gchar* _tmp4_ = NULL;
		gchar* _tmp5_ = NULL;
		GError* _tmp6_ = NULL;
		GError* _tmp7_ = NULL;
		_tmp3_ = script_file;
		_tmp4_ = g_strconcat ("Cannot open script record file ", _tmp3_, NULL);
		_tmp5_ = _tmp4_;
		_tmp6_ = g_error_new_literal (G_FILE_ERROR, G_FILE_ERROR_FAILED, _tmp5_);
		_tmp7_ = _tmp6_;
		_g_free0 (_tmp5_);
		_inner_error_ = _tmp7_;
		if (_inner_error_->domain == G_FILE_ERROR) {
			g_propagate_error (error, _inner_error_);
			_umockdev_script_runner_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	_tmp8_ = device;
	umockdev_script_runner_set_device (self, _tmp8_);
	_tmp9_ = script_file;
	_tmp10_ = g_strdup (_tmp9_);
	_g_free0 (self->priv->script_file);
	self->priv->script_file = _tmp10_;
	_tmp11_ = fd;
	self->priv->fd = _tmp11_;
	self->priv->running = TRUE;
	_tmp12_ = device;
	_tmp13_ = g_thread_new (_tmp12_, _umockdev_script_runner_run_gthread_func, umockdev_script_runner_ref (self));
	_g_thread_unref0 (self->priv->thread);
	self->priv->thread = _tmp13_;
	return self;
}
