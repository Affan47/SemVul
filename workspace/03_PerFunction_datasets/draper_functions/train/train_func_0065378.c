acer_rfkill_exit(void)
{
	if ((ec_raw_mode || !wmi_has_guid(ACERWMID_EVENT_GUID)) &&
	    has_cap(ACER_CAP_WIRELESS | ACER_CAP_BLUETOOTH | ACER_CAP_THREEG))
		cancel_delayed_work_sync(&acer_rfkill_work);

	if (has_cap(ACER_CAP_WIRELESS)) {
		rfkill_unregister(wireless_rfkill);
		rfkill_destroy(wireless_rfkill);
	}

	if (has_cap(ACER_CAP_BLUETOOTH)) {
		rfkill_unregister(bluetooth_rfkill);
		rfkill_destroy(bluetooth_rfkill);
	}

	if (has_cap(ACER_CAP_THREEG)) {
		rfkill_unregister(threeg_rfkill);
		rfkill_destroy(threeg_rfkill);
	}
	return;
}
