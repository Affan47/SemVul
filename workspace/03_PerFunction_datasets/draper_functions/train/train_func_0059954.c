folks_inspect_signal_manager_add_signal_handler (FolksInspectSignalManager* self, GObject* class_instance, guint signal_id, const gchar* detail_string) {
	GClosure* closure = NULL;
	GClosure* _tmp0_ = NULL;
	GClosure* _tmp1_ = NULL;
	GQuark detail_quark = 0U;
	const gchar* _tmp2_ = NULL;
	gulong signal_handler_id = 0UL;
	GObject* _tmp5_ = NULL;
	guint _tmp6_ = 0U;
	GQuark _tmp7_ = 0U;
	GClosure* _tmp8_ = NULL;
	gulong _tmp9_ = 0UL;
	GeeHashMap* signal_handler_ids = NULL;
	GeeHashMap* _tmp10_ = NULL;
	GObject* _tmp11_ = NULL;
	gpointer _tmp12_ = NULL;
	GeeHashMap* _tmp13_ = NULL;
	GeeHashMap* _tmp18_ = NULL;
	guint _tmp19_ = 0U;
	gulong _tmp20_ = 0UL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (class_instance != NULL);
	_tmp0_ = g_closure_new_object ((gulong) sizeof (GClosure), (GObject*) self);
	closure = _tmp0_;
	_tmp1_ = closure;
	g_closure_set_meta_marshal (_tmp1_, NULL, _folks_inspect_signal_manager_signal_meta_marshaller_gclosure_marshal);
	detail_quark = (GQuark) 0;
	_tmp2_ = detail_string;
	if (_tmp2_ != NULL) {
		const gchar* _tmp3_ = NULL;
		GQuark _tmp4_ = 0U;
		_tmp3_ = detail_string;
		_tmp4_ = g_quark_try_string (_tmp3_);
		detail_quark = _tmp4_;
	}
	_tmp5_ = class_instance;
	_tmp6_ = signal_id;
	_tmp7_ = detail_quark;
	_tmp8_ = closure;
	_tmp9_ = g_signal_connect_closure_by_id (_tmp5_, _tmp6_, _tmp7_, _tmp8_, FALSE);
	signal_handler_id = _tmp9_;
	_tmp10_ = self->priv->signals_by_class_instance;
	_tmp11_ = class_instance;
	_tmp12_ = gee_abstract_map_get ((GeeAbstractMap*) _tmp10_, _tmp11_);
	signal_handler_ids = (GeeHashMap*) _tmp12_;
	_tmp13_ = signal_handler_ids;
	if (_tmp13_ == NULL) {
		GeeHashMap* _tmp14_ = NULL;
		GeeHashMap* _tmp15_ = NULL;
		GObject* _tmp16_ = NULL;
		GeeHashMap* _tmp17_ = NULL;
		_tmp14_ = gee_hash_map_new (G_TYPE_UINT, NULL, NULL, G_TYPE_ULONG, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		_g_object_unref0 (signal_handler_ids);
		signal_handler_ids = _tmp14_;
		_tmp15_ = self->priv->signals_by_class_instance;
		_tmp16_ = class_instance;
		_tmp17_ = signal_handler_ids;
		gee_abstract_map_set ((GeeAbstractMap*) _tmp15_, _tmp16_, _tmp17_);
	}
	_tmp18_ = signal_handler_ids;
	_tmp19_ = signal_id;
	_tmp20_ = signal_handler_id;
	gee_abstract_map_set ((GeeAbstractMap*) _tmp18_, (gpointer) ((guintptr) _tmp19_), (gpointer) ((guintptr) _tmp20_));
	_g_object_unref0 (signal_handler_ids);
	_g_closure_unref0 (closure);
}
