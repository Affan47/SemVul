unit_manager_convert_by_symbol (UnitManager* self, Number* x, const gchar* x_symbol, const gchar* z_symbol) {
	Number* result = NULL;
	GList* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (x != NULL, NULL);
	g_return_val_if_fail (x_symbol != NULL, NULL);
	g_return_val_if_fail (z_symbol != NULL, NULL);
	_tmp0_ = self->priv->categories;
	{
		GList* c_collection = NULL;
		GList* c_it = NULL;
		c_collection = _tmp0_;
		for (c_it = c_collection; c_it != NULL; c_it = c_it->next) {
			UnitCategory* _tmp1_ = NULL;
			UnitCategory* c = NULL;
			_tmp1_ = _g_object_ref0 ((UnitCategory*) c_it->data);
			c = _tmp1_;
			{
				Unit* x_units = NULL;
				UnitCategory* _tmp2_ = NULL;
				const gchar* _tmp3_ = NULL;
				Unit* _tmp4_ = NULL;
				Unit* z_units = NULL;
				UnitCategory* _tmp5_ = NULL;
				const gchar* _tmp6_ = NULL;
				Unit* _tmp7_ = NULL;
				gboolean _tmp8_ = FALSE;
				Unit* _tmp9_ = NULL;
				gboolean _tmp11_ = FALSE;
				_tmp2_ = c;
				_tmp3_ = x_symbol;
				_tmp4_ = unit_category_get_unit_by_symbol (_tmp2_, _tmp3_);
				x_units = _tmp4_;
				_tmp5_ = c;
				_tmp6_ = z_symbol;
				_tmp7_ = unit_category_get_unit_by_symbol (_tmp5_, _tmp6_);
				z_units = _tmp7_;
				_tmp9_ = x_units;
				if (_tmp9_ != NULL) {
					Unit* _tmp10_ = NULL;
					_tmp10_ = z_units;
					_tmp8_ = _tmp10_ != NULL;
				} else {
					_tmp8_ = FALSE;
				}
				_tmp11_ = _tmp8_;
				if (_tmp11_) {
					UnitCategory* _tmp12_ = NULL;
					Number* _tmp13_ = NULL;
					Unit* _tmp14_ = NULL;
					Unit* _tmp15_ = NULL;
					Number* _tmp16_ = NULL;
					_tmp12_ = c;
					_tmp13_ = x;
					_tmp14_ = x_units;
					_tmp15_ = z_units;
					_tmp16_ = unit_category_convert (_tmp12_, _tmp13_, _tmp14_, _tmp15_);
					result = _tmp16_;
					_g_object_unref0 (z_units);
					_g_object_unref0 (x_units);
					_g_object_unref0 (c);
					return result;
				}
				_g_object_unref0 (z_units);
				_g_object_unref0 (x_units);
				_g_object_unref0 (c);
			}
		}
	}
	result = NULL;
	return result;
}
