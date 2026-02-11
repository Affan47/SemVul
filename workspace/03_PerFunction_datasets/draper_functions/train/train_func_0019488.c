unity_app_info_manager_register_categories (UnityAppInfoManager* self, const gchar* id, GKeyFile* keyfile) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (id != NULL);
	g_return_if_fail (keyfile != NULL);
	{
		gchar** categories = NULL;
		GKeyFile* _tmp0_ = NULL;
		gsize _tmp1_;
		gchar** _tmp2_ = NULL;
		gint categories_length1 = 0;
		gint _categories_size_ = 0;
		UnityStringArrayWrapper* wrapper = NULL;
		UnityStringArrayWrapper* _tmp3_ = NULL;
		UnityStringArrayWrapper* _tmp4_ = NULL;
		gchar** _tmp5_ = NULL;
		gint _tmp5__length1 = 0;
		GHashTable* _tmp6_ = NULL;
		const gchar* _tmp7_ = NULL;
		gchar* _tmp8_ = NULL;
		UnityStringArrayWrapper* _tmp9_ = NULL;
		_tmp0_ = keyfile;
		_tmp2_ = g_key_file_get_string_list (_tmp0_, "Desktop Entry", "Categories", &_tmp1_, &_inner_error_);
		categories = _tmp2_;
		categories_length1 = _tmp1_;
		_categories_size_ = categories_length1;
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_KEY_FILE_ERROR) {
				goto __catch7_g_key_file_error;
			}
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
		_tmp3_ = unity_string_array_wrapper_new ();
		wrapper = _tmp3_;
		_tmp4_ = wrapper;
		_tmp5_ = categories;
		_tmp5__length1 = categories_length1;
		categories = NULL;
		unity_string_array_wrapper_take_strings (_tmp4_, _tmp5_, _tmp5__length1);
		_tmp6_ = self->priv->categories_by_id;
		_tmp7_ = id;
		_tmp8_ = g_strdup (_tmp7_);
		_tmp9_ = wrapper;
		wrapper = NULL;
		g_hash_table_insert (_tmp6_, _tmp8_, _tmp9_);
		_unity_string_array_wrapper_free0 (wrapper);
		categories = (_vala_array_free (categories, categories_length1, (GDestroyNotify) g_free), NULL);
	}
	goto __finally7;
	__catch7_g_key_file_error:
	{
		GError* eee = NULL;
		eee = _inner_error_;
		_inner_error_ = NULL;
		_g_error_free0 (eee);
	}
	__finally7:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}
