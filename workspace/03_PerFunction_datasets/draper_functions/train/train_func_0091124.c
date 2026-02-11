downloads_directory_monitor_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	DownloadsDirectoryMonitor * self;
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	GError * _inner_error_ = NULL;
	parent_class = G_OBJECT_CLASS (downloads_directory_monitor_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_DOWNLOADS_DIRECTORY_MONITOR, DownloadsDirectoryMonitor);
	_tmp0_ = g_get_user_special_dir (G_USER_DIRECTORY_DOWNLOAD);
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (self->priv->downloads_path);
	self->priv->downloads_path = _tmp1_;
	_tmp2_ = self->priv->downloads_path;
	if (_tmp2_ != NULL) {
		const gchar* _tmp3_ = NULL;
		GFile* _tmp4_ = NULL;
		_tmp3_ = self->priv->downloads_path;
		_tmp4_ = g_file_new_for_path (_tmp3_);
		_g_object_unref0 (self->priv->downloads_directory);
		self->priv->downloads_directory = _tmp4_;
		{
			GFileMonitor* _tmp5_ = NULL;
			GFile* _tmp6_ = NULL;
			GFileMonitor* _tmp7_ = NULL;
			_tmp6_ = self->priv->downloads_directory;
			_tmp7_ = g_file_monitor_directory (_tmp6_, G_FILE_MONITOR_NONE, NULL, &_inner_error_);
			_tmp5_ = _tmp7_;
			if (_inner_error_ != NULL) {
				goto __catch2_g_error;
			}
			_g_object_unref0 (self->priv->monitor);
			self->priv->monitor = _tmp5_;
		}
		goto __finally2;
		__catch2_g_error:
		{
			GError* err = NULL;
			GError* _tmp8_ = NULL;
			const gchar* _tmp9_ = NULL;
			err = _inner_error_;
			_inner_error_ = NULL;
			_tmp8_ = err;
			_tmp9_ = _tmp8_->message;
			g_warning ("downloads-directory-provider.vala:66: Couldn't set up monitor on Downl" \
"oads directory: %s", _tmp9_);
			_g_error_free0 (err);
		}
		__finally2:
		if (_inner_error_ != NULL) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
		}
	}
	return obj;
}
