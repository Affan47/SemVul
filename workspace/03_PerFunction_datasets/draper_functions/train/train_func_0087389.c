unity_app_info_manager_on_dir_changed (UnityAppInfoManager* self, GFileMonitor* mon, GFile* file, GFile* other_file, GFileMonitorEvent e) {
	gchar* desktop_id = NULL;
	GFile* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	gchar* path = NULL;
	GFile* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	GAppInfo* appinfo = NULL;
	GHashTable* _tmp4_ = NULL;
	const gchar* _tmp5_ = NULL;
	gboolean _tmp6_ = FALSE;
	GHashTable* _tmp11_ = NULL;
	const gchar* _tmp12_ = NULL;
	gboolean _tmp13_ = FALSE;
	g_return_if_fail (self != NULL);
	g_return_if_fail (mon != NULL);
	g_return_if_fail (file != NULL);
	_tmp0_ = file;
	_tmp1_ = g_file_get_basename (_tmp0_);
	desktop_id = _tmp1_;
	_tmp2_ = file;
	_tmp3_ = g_file_get_path (_tmp2_);
	path = _tmp3_;
	_tmp4_ = self->priv->appinfo_by_id;
	_tmp5_ = desktop_id;
	_tmp6_ = g_hash_table_remove (_tmp4_, _tmp5_);
	if (_tmp6_) {
		const gchar* _tmp7_ = NULL;
		GAppInfo* _tmp8_ = NULL;
		const gchar* _tmp9_ = NULL;
		GAppInfo* _tmp10_ = NULL;
		_tmp7_ = desktop_id;
		_tmp8_ = unity_app_info_manager_lookup (self, _tmp7_);
		_g_object_unref0 (appinfo);
		appinfo = _tmp8_;
		_tmp9_ = desktop_id;
		_tmp10_ = appinfo;
		g_signal_emit_by_name (self, "changed", _tmp9_, _tmp10_);
	}
	_tmp11_ = self->priv->appinfo_by_id;
	_tmp12_ = path;
	_tmp13_ = g_hash_table_remove (_tmp11_, _tmp12_);
	if (_tmp13_) {
		const gchar* _tmp14_ = NULL;
		GAppInfo* _tmp15_ = NULL;
		const gchar* _tmp16_ = NULL;
		GAppInfo* _tmp17_ = NULL;
		_tmp14_ = path;
		_tmp15_ = unity_app_info_manager_lookup (self, _tmp14_);
		_g_object_unref0 (appinfo);
		appinfo = _tmp15_;
		_tmp16_ = path;
		_tmp17_ = appinfo;
		g_signal_emit_by_name (self, "changed", _tmp16_, _tmp17_);
	}
	_g_object_unref0 (appinfo);
	_g_free0 (path);
	_g_free0 (desktop_id);
}
