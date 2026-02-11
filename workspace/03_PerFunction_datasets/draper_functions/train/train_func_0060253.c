fso_register_function (GTypeModule* module) {
	FsoFrameworkLogger* _tmp0_ = NULL;
	g_return_if_fail (module != NULL);
	dbus_service_resource_register_type (module);
	fso_gsm_service_register_type (module);
	fso_gsm_service_manager_register_type (module);
	fso_gsm_device_service_manager_register_type (module);
	fso_gsm_modem_factory_register_type (module);
	fso_gsm_info_service_register_type (module);
	fso_gsm_device_power_supply_service_register_type (module);
	fso_gsm_device_rtc_service_register_type (module);
	fso_gsm_gsm_debug_service_register_type (module);
	fso_gsm_gsm_device_service_register_type (module);
	fso_gsm_gsm_sim_service_register_type (module);
	fso_gsm_gsm_sms_service_register_type (module);
	fso_gsm_gsm_network_service_register_type (module);
	fso_gsm_gsm_call_service_register_type (module);
	fso_gsm_gsm_call_forwarding_service_register_type (module);
	fso_gsm_gsm_hz_service_register_type (module);
	fso_gsm_gsm_cb_service_register_type (module);
	fso_gsm_gsm_voice_mail_service_register_type (module);
	fso_gsm_gsm_monitor_service_register_type (module);
	fso_gsm_gsm_pdp_service_register_type (module);
	_tmp0_ = fso_framework_theLogger;
	fso_framework_logger_debug (_tmp0_, "fsogsm.dbus_service fso_register_function");
}
