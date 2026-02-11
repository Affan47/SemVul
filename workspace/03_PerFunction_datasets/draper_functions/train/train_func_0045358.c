telephony_call_hold_req(void *telephony_device, const char *cmd)
{
	const char *idx;
	struct csd_call *call;
	int err = 0;

	DBG("telephony-maemo6: got call hold request %s", cmd);

	if (strlen(cmd) > 1)
		idx = &cmd[1];
	else
		idx = NULL;

	if (idx)
		call = g_slist_nth_data(calls, strtol(idx, NULL, 0) - 1);
	else
		call = NULL;

	switch (cmd[0]) {
	case '0':
		if (find_call_with_status(CSD_CALL_STATUS_WAITING))
			foreach_call_with_status(CSD_CALL_STATUS_WAITING,
								release_call);
		else
			foreach_call_with_status(CSD_CALL_STATUS_HOLD,
								release_call);
		break;
	case '1':
		if (idx) {
			if (call)
				err = release_call(call);
			break;
		}
		foreach_call_with_status(CSD_CALL_STATUS_ACTIVE, release_call);
		call = find_call_with_status(CSD_CALL_STATUS_WAITING);
		if (call)
			err = answer_call(call);
		break;
	case '2':
		if (idx) {
			if (call)
				err = split_call(call);
		} else {
			struct csd_call *held, *wait;

			call = find_call_with_status(CSD_CALL_STATUS_ACTIVE);
			held = find_call_with_status(CSD_CALL_STATUS_HOLD);
			wait = find_call_with_status(CSD_CALL_STATUS_WAITING);

			if (wait)
				err = answer_call(wait);
			else if (call && held)
				err = swap_calls();
			else {
				if (call)
					err = hold_call(call);
				if (held)
					err = unhold_call(held);
			}
		}
		break;
	case '3':
		if (find_call_with_status(CSD_CALL_STATUS_HOLD) ||
				find_call_with_status(CSD_CALL_STATUS_WAITING))
			err = create_conference();
		break;
	case '4':
		err = call_transfer();
		break;
	default:
		DBG("Unknown call hold request");
		break;
	}

	if (err)
		telephony_call_hold_rsp(telephony_device,
					CME_ERROR_AG_FAILURE);
	else
		telephony_call_hold_rsp(telephony_device, CME_ERROR_NONE);
}
