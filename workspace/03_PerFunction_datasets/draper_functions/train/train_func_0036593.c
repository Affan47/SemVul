main_on_bus_acquired (GDBusConnection* _conn) {
	GDBusConnection* _tmp0_ = NULL;
	DVBManager* _tmp1_ = NULL;
	GDBusConnection* _tmp2_ = NULL;
	GDBusConnection* _tmp3_ = NULL;
	g_return_if_fail (_conn != NULL);
	_tmp0_ = _conn;
	_tmp1_ = main_manager;
	dvb_utils_dbus_register_object (DVB_TYPE_ID_BUS_MANAGER, (GBoxedCopyFunc) g_object_ref, g_object_unref, _tmp0_, DVB_CONSTANTS_DBUS_MANAGER_PATH, (DVBIDBusManager*) _tmp1_);
	_tmp2_ = _conn;
	_tmp3_ = _g_object_ref0 (_tmp2_);
	_g_object_unref0 (main_conn);
	main_conn = _tmp3_;
	main_start_recordings_store ();
	main_restore_device_groups ();
}
