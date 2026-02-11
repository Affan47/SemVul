telephony_device_connected(void *telephony_device)
{
	struct csd_call *coming;

	DBG("telephony-maemo6: device %p connected", telephony_device);

	coming = find_call_with_status(CSD_CALL_STATUS_MT_ALERTING);
	if (coming) {
		if (find_call_with_status(CSD_CALL_STATUS_ACTIVE))
			telephony_call_waiting_ind(coming->number,
						number_type(coming->number));
		else
			telephony_incoming_call_ind(coming->number,
						number_type(coming->number));
	}
}
