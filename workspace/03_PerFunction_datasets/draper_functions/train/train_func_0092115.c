fso_gsm_mbpi_country_finalize (FsoGsmMBPICountry* obj) {
	FsoGsmMBPICountry * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, FSO_GSM_MBPI_TYPE_COUNTRY, FsoGsmMBPICountry);
	_g_free0 (self->code);
	_g_free0 (self->name);
	_g_free0 (self->dialprefix);
	_g_object_unref0 (self->providers);
	_g_object_unref0 (self->timezones);
}
