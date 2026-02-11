folks_inspect_signal_manager_add_emission_hook (FolksInspectSignalManager* self, GType class_type, guint signal_id, const gchar* detail_string) {
	gboolean result = FALSE;
	GQuark detail_quark = 0U;
	const gchar* _tmp0_ = NULL;
	GSignalQuery query = {0};
	guint _tmp3_ = 0U;
	GSignalQuery _tmp4_ = {0};
	GSignalQuery _tmp5_ = {0};
	GSignalFlags _tmp6_ = 0;
	gulong hook_id = 0UL;
	guint _tmp7_ = 0U;
	GQuark _tmp8_ = 0U;
	gulong _tmp9_ = 0UL;
	GeeHashMap* hook_ids = NULL;
	GeeHashMap* _tmp10_ = NULL;
	GType _tmp11_ = 0UL;
	gpointer _tmp12_ = NULL;
	GeeHashMap* _tmp13_ = NULL;
	GeeHashMap* _tmp18_ = NULL;
	guint _tmp19_ = 0U;
	gulong _tmp20_ = 0UL;
	g_return_val_if_fail (self != NULL, FALSE);
	detail_quark = (GQuark) 0;
	_tmp0_ = detail_string;
	if (_tmp0_ != NULL) {
		const gchar* _tmp1_ = NULL;
		GQuark _tmp2_ = 0U;
		_tmp1_ = detail_string;
		_tmp2_ = g_quark_try_string (_tmp1_);
		detail_quark = _tmp2_;
	}
	_tmp3_ = signal_id;
	g_signal_query (_tmp3_, &_tmp4_);
	query = _tmp4_;
	_tmp5_ = query;
	_tmp6_ = _tmp5_.signal_flags;
	if ((_tmp6_ & G_SIGNAL_NO_HOOKS) != 0) {
		result = FALSE;
		return result;
	}
	_tmp7_ = signal_id;
	_tmp8_ = detail_quark;
	_tmp9_ = g_signal_add_emission_hook (_tmp7_, _tmp8_, _folks_inspect_signal_manager_emission_hook_cb_gsignal_emission_hook, self, NULL);
	hook_id = _tmp9_;
	_tmp10_ = self->priv->signals_by_class_type;
	_tmp11_ = class_type;
	_tmp12_ = gee_abstract_map_get ((GeeAbstractMap*) _tmp10_, (gpointer) ((gintptr) _tmp11_));
	hook_ids = (GeeHashMap*) _tmp12_;
	_tmp13_ = hook_ids;
	if (_tmp13_ == NULL) {
		GeeHashMap* _tmp14_ = NULL;
		GeeHashMap* _tmp15_ = NULL;
		GType _tmp16_ = 0UL;
		GeeHashMap* _tmp17_ = NULL;
		_tmp14_ = gee_hash_map_new (G_TYPE_UINT, NULL, NULL, G_TYPE_ULONG, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		_g_object_unref0 (hook_ids);
		hook_ids = _tmp14_;
		_tmp15_ = self->priv->signals_by_class_type;
		_tmp16_ = class_type;
		_tmp17_ = hook_ids;
		gee_abstract_map_set ((GeeAbstractMap*) _tmp15_, (gpointer) ((gintptr) _tmp16_), _tmp17_);
	}
	_tmp18_ = hook_ids;
	_tmp19_ = signal_id;
	_tmp20_ = hook_id;
	gee_abstract_map_set ((GeeAbstractMap*) _tmp18_, (gpointer) ((guintptr) _tmp19_), (gpointer) ((guintptr) _tmp20_));
	result = TRUE;
	_g_object_unref0 (hook_ids);
	return result;
}
