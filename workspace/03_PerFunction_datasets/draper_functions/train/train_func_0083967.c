fso_framework_smart_key_file_sectionsWithPrefix (FsoFrameworkSmartKeyFile* self, const gchar* prefix) {
	GList* result = NULL;
	GList* list = NULL;
	gchar** groups = NULL;
	GKeyFile* _tmp0_ = NULL;
	gsize _tmp1_;
	gchar** _tmp2_ = NULL;
	gint groups_length1 = 0;
	gint _groups_size_ = 0;
	gchar** _tmp3_ = NULL;
	gint _tmp3__length1 = 0;
	g_return_val_if_fail (self != NULL, NULL);
	list = NULL;
	_tmp0_ = self->priv->kf;
	_tmp2_ = g_key_file_get_groups (_tmp0_, &_tmp1_);
	groups = _tmp2_;
	groups_length1 = _tmp1_;
	_groups_size_ = groups_length1;
	_tmp3_ = groups;
	_tmp3__length1 = groups_length1;
	{
		gchar** group_collection = NULL;
		gint group_collection_length1 = 0;
		gint _group_collection_size_ = 0;
		gint group_it = 0;
		group_collection = _tmp3_;
		group_collection_length1 = _tmp3__length1;
		for (group_it = 0; group_it < _tmp3__length1; group_it = group_it + 1) {
			gchar* _tmp4_ = NULL;
			gchar* group = NULL;
			_tmp4_ = g_strdup (group_collection[group_it]);
			group = _tmp4_;
			{
				const gchar* _tmp5_ = NULL;
				_tmp5_ = prefix;
				if (_tmp5_ == NULL) {
					const gchar* _tmp6_ = NULL;
					gchar* _tmp7_ = NULL;
					_tmp6_ = group;
					_tmp7_ = g_strdup (_tmp6_);
					list = g_list_append (list, _tmp7_);
				} else {
					const gchar* _tmp8_ = NULL;
					const gchar* _tmp9_ = NULL;
					gboolean _tmp10_ = FALSE;
					_tmp8_ = group;
					_tmp9_ = prefix;
					_tmp10_ = g_str_has_prefix (_tmp8_, _tmp9_);
					if (_tmp10_) {
						const gchar* _tmp11_ = NULL;
						gchar* _tmp12_ = NULL;
						_tmp11_ = group;
						_tmp12_ = g_strdup (_tmp11_);
						list = g_list_append (list, _tmp12_);
					}
				}
				_g_free0 (group);
			}
		}
	}
	result = list;
	groups = (_vala_array_free (groups, groups_length1, (GDestroyNotify) g_free), NULL);
	return result;
}
