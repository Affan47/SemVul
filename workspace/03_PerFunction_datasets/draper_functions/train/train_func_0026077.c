currency_manager_get_currency (CurrencyManager* self, const gchar* name) {
	Currency* result = NULL;
	GList* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	_tmp0_ = self->priv->currencies;
	{
		GList* c_collection = NULL;
		GList* c_it = NULL;
		c_collection = _tmp0_;
		for (c_it = c_collection; c_it != NULL; c_it = c_it->next) {
			Currency* _tmp1_ = NULL;
			Currency* c = NULL;
			_tmp1_ = _g_object_ref0 ((Currency*) c_it->data);
			c = _tmp1_;
			{
				const gchar* _tmp2_ = NULL;
				Currency* _tmp3_ = NULL;
				gchar* _tmp4_ = NULL;
				gchar* _tmp5_ = NULL;
				gchar* _tmp6_ = NULL;
				gboolean _tmp7_ = FALSE;
				_tmp2_ = name;
				_tmp3_ = c;
				_tmp4_ = currency_get_name (_tmp3_);
				_tmp5_ = _tmp4_;
				_tmp6_ = _tmp5_;
				_tmp7_ = g_strcmp0 (_tmp2_, _tmp6_) == 0;
				_g_free0 (_tmp6_);
				if (_tmp7_) {
					Number* value = NULL;
					Currency* _tmp8_ = NULL;
					Number* _tmp9_ = NULL;
					gboolean _tmp10_ = FALSE;
					gboolean _tmp11_ = FALSE;
					Number* _tmp12_ = NULL;
					gboolean _tmp15_ = FALSE;
					gboolean _tmp18_ = FALSE;
					_tmp8_ = c;
					_tmp9_ = currency_get_value (_tmp8_);
					value = _tmp9_;
					_tmp12_ = value;
					if (_tmp12_ == NULL) {
						_tmp11_ = TRUE;
					} else {
						Number* _tmp13_ = NULL;
						gboolean _tmp14_ = FALSE;
						_tmp13_ = value;
						_tmp14_ = number_is_negative (_tmp13_);
						_tmp11_ = _tmp14_;
					}
					_tmp15_ = _tmp11_;
					if (_tmp15_) {
						_tmp10_ = TRUE;
					} else {
						Number* _tmp16_ = NULL;
						gboolean _tmp17_ = FALSE;
						_tmp16_ = value;
						_tmp17_ = number_is_zero (_tmp16_);
						_tmp10_ = _tmp17_;
					}
					_tmp18_ = _tmp10_;
					if (_tmp18_) {
						result = NULL;
						_number_unref0 (value);
						_g_object_unref0 (c);
						return result;
					} else {
						result = c;
						_number_unref0 (value);
						return result;
					}
					_number_unref0 (value);
				}
				_g_object_unref0 (c);
			}
		}
	}
	result = NULL;
	return result;
}
