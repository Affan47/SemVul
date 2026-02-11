fso_gsm_phonebook_storage_real_repr (FsoFrameworkAbstractObject* base) {
	FsoGsmPhonebookStorage * self;
	gchar* result = NULL;
	gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	self = (FsoGsmPhonebookStorage*) base;
	_tmp1_ = self->priv->imsi;
	if (_tmp1_ != NULL) {
		const gchar* _tmp2_ = NULL;
		const gchar* _tmp3_ = NULL;
		gchar* _tmp4_ = NULL;
		_tmp2_ = self->priv->imsi;
		_tmp3_ = string_to_string (_tmp2_);
		_tmp4_ = g_strconcat ("<", _tmp3_, ">", NULL);
		_g_free0 (_tmp0_);
		_tmp0_ = _tmp4_;
	} else {
		gchar* _tmp5_ = NULL;
		_tmp5_ = g_strdup ("<>");
		_g_free0 (_tmp0_);
		_tmp0_ = _tmp5_;
	}
	result = _tmp0_;
	return result;
}
