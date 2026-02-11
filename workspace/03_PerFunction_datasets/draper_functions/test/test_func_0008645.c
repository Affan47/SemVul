tracker_query_get_tags_filter (TrackerQuery* self) {
	gchar* result = NULL;
	gchar* filter = NULL;
	gchar* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	GPtrArray* _tmp2_ = NULL;
	gboolean _tmp6_ = FALSE;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = g_strdup ("");
	filter = _tmp0_;
	_tmp2_ = self->priv->_tags;
	if (_tmp2_ != NULL) {
		GPtrArray* _tmp3_ = NULL;
		gint _tmp4_ = 0;
		gint _tmp5_ = 0;
		_tmp3_ = self->priv->_tags;
		_tmp4_ = g_ptr_array_get_length (_tmp3_);
		_tmp5_ = _tmp4_;
		_tmp1_ = _tmp5_ > 0;
	} else {
		_tmp1_ = FALSE;
	}
	_tmp6_ = _tmp1_;
	if (_tmp6_) {
		{
			gint i = 0;
			i = 0;
			{
				gboolean _tmp7_ = FALSE;
				_tmp7_ = TRUE;
				while (TRUE) {
					gboolean _tmp8_ = FALSE;
					gint _tmp10_ = 0;
					GPtrArray* _tmp11_ = NULL;
					gint _tmp12_ = 0;
					gint _tmp13_ = 0;
					gchar* escaped = NULL;
					GPtrArray* _tmp14_ = NULL;
					gint _tmp15_ = 0;
					gconstpointer _tmp16_ = NULL;
					gchar* _tmp17_ = NULL;
					const gchar* _tmp18_ = NULL;
					gint _tmp19_ = 0;
					gint _tmp20_ = 0;
					const gchar* _tmp23_ = NULL;
					const gchar* _tmp24_ = NULL;
					gchar* _tmp25_ = NULL;
					gchar* _tmp26_ = NULL;
					gchar* _tmp27_ = NULL;
					_tmp8_ = _tmp7_;
					if (!_tmp8_) {
						gint _tmp9_ = 0;
						_tmp9_ = i;
						i = _tmp9_ + 1;
					}
					_tmp7_ = FALSE;
					_tmp10_ = i;
					_tmp11_ = self->priv->_tags;
					_tmp12_ = g_ptr_array_get_length (_tmp11_);
					_tmp13_ = _tmp12_;
					if (!(_tmp10_ < _tmp13_)) {
						break;
					}
					_tmp14_ = self->priv->_tags;
					_tmp15_ = i;
					_tmp16_ = g_ptr_array_index (_tmp14_, (guint) _tmp15_);
					_tmp17_ = tracker_sparql_escape_string ((const gchar*) _tmp16_);
					escaped = _tmp17_;
					_tmp18_ = filter;
					_tmp19_ = strlen (_tmp18_);
					_tmp20_ = _tmp19_;
					if (_tmp20_ > 1) {
						const gchar* _tmp21_ = NULL;
						gchar* _tmp22_ = NULL;
						_tmp21_ = filter;
						_tmp22_ = g_strconcat (_tmp21_, ", ", NULL);
						_g_free0 (filter);
						filter = _tmp22_;
					}
					_tmp23_ = filter;
					_tmp24_ = escaped;
					_tmp25_ = g_strdup_printf ("\"%s\"", _tmp24_);
					_tmp26_ = _tmp25_;
					_tmp27_ = g_strconcat (_tmp23_, _tmp26_, NULL);
					_g_free0 (filter);
					filter = _tmp27_;
					_g_free0 (_tmp26_);
					_g_free0 (escaped);
				}
			}
		}
	}
	result = filter;
	return result;
}
