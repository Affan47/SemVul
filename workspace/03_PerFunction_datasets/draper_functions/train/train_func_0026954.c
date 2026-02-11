fso_gsm_abstract_modem_mediatorFactory (FsoGsmAbstractModem* self, GType mediator, GError** error) {
	GType result = 0UL;
	GType typ = 0UL;
	GeeHashMap* _tmp0_ = NULL;
	GType _tmp1_ = 0UL;
	gpointer _tmp2_ = NULL;
	GType _tmp3_ = 0UL;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, 0UL);
	_tmp0_ = self->mediators;
	_tmp1_ = mediator;
	_tmp2_ = gee_abstract_map_get ((GeeAbstractMap*) _tmp0_, (gpointer) ((gintptr) _tmp1_));
	typ = (GType) ((gintptr) _tmp2_);
	_tmp3_ = typ;
	if (_tmp3_ == G_TYPE_INVALID) {
		GType _tmp4_ = 0UL;
		const gchar* _tmp5_ = NULL;
		const gchar* _tmp6_ = NULL;
		gchar* _tmp7_ = NULL;
		gchar* _tmp8_ = NULL;
		GError* _tmp9_ = NULL;
		GError* _tmp10_ = NULL;
		_tmp4_ = mediator;
		_tmp5_ = g_type_name (_tmp4_);
		_tmp6_ = string_to_string (_tmp5_);
		_tmp7_ = g_strconcat ("Requested mediator ", _tmp6_, " unknown", NULL);
		_tmp8_ = _tmp7_;
		_tmp9_ = g_error_new_literal (FREE_SMARTPHONE_ERROR, FREE_SMARTPHONE_ERROR_INTERNAL_ERROR, _tmp8_);
		_tmp10_ = _tmp9_;
		_g_free0 (_tmp8_);
		_inner_error_ = _tmp10_;
		if (_inner_error_->domain == FREE_SMARTPHONE_ERROR) {
			g_propagate_error (error, _inner_error_);
			return 0UL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return 0UL;
		}
	}
	result = typ;
	return result;
}
