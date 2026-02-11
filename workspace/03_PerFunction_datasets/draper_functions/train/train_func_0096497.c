fso_gsm_gsm_sim_service_real_get_home_zone_parameters_data_free (gpointer _data) {
	FsoGsmGsmSimServiceGetHomeZoneParametersData* _data_;
	_data_ = _data;
	_data_->result = (_vala_FreeSmartphoneGSMSIMHomeZone_array_free (_data_->result, _data_->result_length1), NULL);
	_g_object_unref0 (_data_->self);
	g_slice_free (FsoGsmGsmSimServiceGetHomeZoneParametersData, _data_);
}
