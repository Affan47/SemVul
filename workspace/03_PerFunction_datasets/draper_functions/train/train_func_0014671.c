tracker_tags_view_set_files (TrackerTagsView* self, GList* _files) {
	GList* _tmp0_;
	GList* _tmp3_;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->files;
	if (_tmp0_ != NULL) {
		GList* _tmp1_;
		_tmp1_ = self->priv->files;
		{
			GList* url_collection = NULL;
			GList* url_it = NULL;
			url_collection = _tmp1_;
			for (url_it = url_collection; url_it != NULL; url_it = url_it->next) {
				gchar* _tmp2_;
				gchar* url = NULL;
				_tmp2_ = g_strdup ((const gchar*) url_it->data);
				url = _tmp2_;
				{
					_g_free0 (url);
					url = NULL;
					_g_free0 (url);
				}
			}
		}
		__g_list_free__g_free0_0 (self->priv->files);
		self->priv->files = NULL;
	}
	_tmp3_ = _files;
	if (_tmp3_ != NULL) {
		GList* _tmp4_;
		_tmp4_ = _files;
		{
			GList* url_collection = NULL;
			GList* url_it = NULL;
			url_collection = _tmp4_;
			for (url_it = url_collection; url_it != NULL; url_it = url_it->next) {
				gchar* _tmp5_;
				gchar* url = NULL;
				_tmp5_ = g_strdup ((const gchar*) url_it->data);
				url = _tmp5_;
				{
					const gchar* _tmp6_;
					gchar* _tmp7_;
					_tmp6_ = url;
					_tmp7_ = g_strdup (_tmp6_);
					self->priv->files = g_list_prepend (self->priv->files, _tmp7_);
					_g_free0 (url);
				}
			}
		}
		self->priv->files = g_list_reverse (self->priv->files);
	}
	tracker_tags_view_update_for_files (self);
}
