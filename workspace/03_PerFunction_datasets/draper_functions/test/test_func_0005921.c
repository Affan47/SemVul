telephony_terminate_call_req(void *telephony_device)
{
	struct csd_call *call;
	struct csd_call *alerting;
	int err;

	call = find_call_with_status(CSD_CALL_STATUS_ACTIVE);
	if (!call)
		call = find_non_idle_call();

	if (!call) {
		error("No active call");
		telephony_terminate_call_rsp(telephony_device,
						CME_ERROR_NOT_ALLOWED);
		return;
	}

	alerting = find_call_with_status(CSD_CALL_STATUS_MO_ALERTING);
	if (call->on_hold && alerting)
		err = release_call(alerting);
	else if (call->conference)
		err = release_conference();
	else
		err = release_call(call);

	if (err < 0)
		telephony_terminate_call_rsp(telephony_device,
						CME_ERROR_AG_FAILURE);
	else
		telephony_terminate_call_rsp(telephony_device, CME_ERROR_NONE);
}
