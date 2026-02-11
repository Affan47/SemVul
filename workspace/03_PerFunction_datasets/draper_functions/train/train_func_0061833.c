folks_inspect_utils_persona_store_id_completion_cb (const gchar* word, gint state) {
	gchar* result = NULL;
	gint _tmp0_ = 0;
	g_return_val_if_fail (word != NULL, NULL);
	_tmp0_ = state;
	if (_tmp0_ == 0) {
		FolksInspectClient* _tmp1_ = NULL;
		FolksBackendStore* _tmp2_ = NULL;
		FolksBackendStore* _tmp3_ = NULL;
		GeeCollection* _tmp4_ = NULL;
		GeeCollection* _tmp5_ = NULL;
		GeeIterator* _tmp6_ = NULL;
		_tmp1_ = main_client;
		_tmp2_ = folks_inspect_client_get_backend_store (_tmp1_);
		_tmp3_ = _tmp2_;
		_tmp4_ = folks_backend_store_list_backends (_tmp3_);
		_tmp5_ = _tmp4_;
		_tmp6_ = gee_iterable_iterator ((GeeIterable*) _tmp5_);
		_g_object_unref0 (folks_inspect_utils_backend_name_iter);
		folks_inspect_utils_backend_name_iter = _tmp6_;
		_g_object_unref0 (_tmp5_);
		_g_object_unref0 (folks_inspect_utils_persona_store_id_iter);
		folks_inspect_utils_persona_store_id_iter = NULL;
	}
	while (TRUE) {
		gboolean _tmp7_ = FALSE;
		GeeMapIterator* _tmp8_ = NULL;
		gboolean _tmp11_ = FALSE;
		GeeMapIterator* _tmp12_ = NULL;
		_tmp8_ = folks_inspect_utils_persona_store_id_iter;
		if (_tmp8_ != NULL) {
			_tmp7_ = TRUE;
		} else {
			GeeIterator* _tmp9_ = NULL;
			gboolean _tmp10_ = FALSE;
			_tmp9_ = folks_inspect_utils_backend_name_iter;
			_tmp10_ = gee_iterator_next (_tmp9_);
			_tmp7_ = _tmp10_ == TRUE;
		}
		_tmp11_ = _tmp7_;
		if (!_tmp11_) {
			break;
		}
		_tmp12_ = folks_inspect_utils_persona_store_id_iter;
		if (_tmp12_ == NULL) {
			FolksBackend* backend = NULL;
			GeeIterator* _tmp13_ = NULL;
			gpointer _tmp14_ = NULL;
			FolksBackend* _tmp15_ = NULL;
			GeeMap* _tmp16_ = NULL;
			GeeMap* _tmp17_ = NULL;
			GeeMapIterator* _tmp18_ = NULL;
			_tmp13_ = folks_inspect_utils_backend_name_iter;
			_tmp14_ = gee_iterator_get (_tmp13_);
			backend = (FolksBackend*) _tmp14_;
			_tmp15_ = backend;
			_tmp16_ = folks_backend_get_persona_stores (_tmp15_);
			_tmp17_ = _tmp16_;
			_tmp18_ = gee_map_map_iterator (_tmp17_);
			_g_object_unref0 (folks_inspect_utils_persona_store_id_iter);
			folks_inspect_utils_persona_store_id_iter = _tmp18_;
			_g_object_unref0 (backend);
		}
		while (TRUE) {
			GeeMapIterator* _tmp19_ = NULL;
			gboolean _tmp20_ = FALSE;
			gchar* id = NULL;
			GeeMapIterator* _tmp21_ = NULL;
			gpointer _tmp22_ = NULL;
			const gchar* _tmp23_ = NULL;
			const gchar* _tmp24_ = NULL;
			gboolean _tmp25_ = FALSE;
			_tmp19_ = folks_inspect_utils_persona_store_id_iter;
			_tmp20_ = gee_map_iterator_next (_tmp19_);
			if (!(_tmp20_ == TRUE)) {
				break;
			}
			_tmp21_ = folks_inspect_utils_persona_store_id_iter;
			_tmp22_ = gee_map_iterator_get_key (_tmp21_);
			id = (gchar*) _tmp22_;
			_tmp23_ = id;
			_tmp24_ = word;
			_tmp25_ = g_str_has_prefix (_tmp23_, _tmp24_);
			if (_tmp25_) {
				result = id;
				return result;
			}
			_g_free0 (id);
		}
		_g_object_unref0 (folks_inspect_utils_persona_store_id_iter);
		folks_inspect_utils_persona_store_id_iter = NULL;
	}
	_g_object_unref0 (folks_inspect_utils_backend_name_iter);
	folks_inspect_utils_backend_name_iter = NULL;
	result = NULL;
	return result;
}
