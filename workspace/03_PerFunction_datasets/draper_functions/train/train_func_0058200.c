utils_extract_desktop_id (const gchar* path) {
	gchar* result = NULL;
	const gchar* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	gchar* normalized_path = NULL;
	const gchar* _tmp4_ = NULL;
	gchar* _tmp5_ = NULL;
	gchar** _tmp6_ = NULL;
	gint _tmp6__length1 = 0;
	const gchar* _tmp19_ = NULL;
	gchar* _tmp20_ = NULL;
	g_return_val_if_fail (path != NULL, NULL);
	_tmp0_ = path;
	_tmp1_ = g_str_has_prefix (_tmp0_, "/");
	if (!_tmp1_) {
		const gchar* _tmp2_ = NULL;
		gchar* _tmp3_ = NULL;
		_tmp2_ = path;
		_tmp3_ = g_strdup (_tmp2_);
		result = _tmp3_;
		return result;
	}
	_tmp4_ = path;
	_tmp5_ = string_replace (_tmp4_, "//", "/");
	normalized_path = _tmp5_;
	_tmp6_ = utils_desktop_file_prefixes;
	_tmp6__length1 = utils_desktop_file_prefixes_length1;
	{
		gchar** prefix_collection = NULL;
		gint prefix_collection_length1 = 0;
		gint _prefix_collection_size_ = 0;
		gint prefix_it = 0;
		prefix_collection = _tmp6_;
		prefix_collection_length1 = _tmp6__length1;
		for (prefix_it = 0; prefix_it < _tmp6__length1; prefix_it = prefix_it + 1) {
			const gchar* prefix = NULL;
			prefix = prefix_collection[prefix_it];
			{
				const gchar* _tmp7_ = NULL;
				const gchar* _tmp8_ = NULL;
				gboolean _tmp9_ = FALSE;
				_tmp7_ = normalized_path;
				_tmp8_ = prefix;
				_tmp9_ = g_str_has_prefix (_tmp7_, _tmp8_);
				if (_tmp9_) {
					gchar* without_prefix = NULL;
					const gchar* _tmp10_ = NULL;
					const gchar* _tmp11_ = NULL;
					gint _tmp12_ = 0;
					gint _tmp13_ = 0;
					gchar* _tmp14_ = NULL;
					const gchar* _tmp15_ = NULL;
					gboolean _tmp16_ = FALSE;
					_tmp10_ = normalized_path;
					_tmp11_ = prefix;
					_tmp12_ = strlen (_tmp11_);
					_tmp13_ = _tmp12_;
					_tmp14_ = string_substring (_tmp10_, (glong) _tmp13_, (glong) (-1));
					without_prefix = _tmp14_;
					_tmp15_ = without_prefix;
					_tmp16_ = string_contains (_tmp15_, G_DIR_SEPARATOR_S);
					if (_tmp16_) {
						const gchar* _tmp17_ = NULL;
						gchar* _tmp18_ = NULL;
						_tmp17_ = without_prefix;
						_tmp18_ = string_replace (_tmp17_, G_DIR_SEPARATOR_S, "-");
						result = _tmp18_;
						_g_free0 (without_prefix);
						_g_free0 (normalized_path);
						return result;
					}
					result = without_prefix;
					_g_free0 (normalized_path);
					return result;
				}
			}
		}
	}
	_tmp19_ = path;
	_tmp20_ = g_path_get_basename (_tmp19_);
	result = _tmp20_;
	_g_free0 (normalized_path);
	return result;
}
