telephony_init(void)
{
	uint32_t features = AG_FEATURE_REJECT_A_CALL |
				AG_FEATURE_ENHANCED_CALL_STATUS |
				AG_FEATURE_EXTENDED_ERROR_RESULT_CODES;

	DBG("");

	connection = dbus_bus_get(DBUS_BUS_SYSTEM, NULL);

	if (g_dbus_register_interface(connection, TELEPHONY_DUMMY_PATH,
					TELEPHONY_DUMMY_IFACE,
					dummy_methods, dummy_signals,
					NULL, NULL, NULL) == FALSE) {
		error("telephony-dummy interface %s init failed on path %s",
			TELEPHONY_DUMMY_IFACE, TELEPHONY_DUMMY_PATH);
		return -1;
	}

	telephony_ready_ind(features, dummy_indicators, BTRH_NOT_SUPPORTED,
								chld_str);

	return 0;
}
