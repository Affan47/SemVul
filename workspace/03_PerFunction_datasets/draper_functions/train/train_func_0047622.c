telephony_list_current_calls_req(void *telephony_device)
{
	GSList *l;
	int i;

	DBG("telephony-ofono: list current calls request");

	for (l = calls, i = 1; l != NULL; l = l->next, i++) {
		struct voice_call *vc = l->data;
		int direction, multiparty;

		direction = vc->originating ?
				CALL_DIR_OUTGOING : CALL_DIR_INCOMING;

		multiparty = vc->conference ?
				CALL_MULTIPARTY_YES : CALL_MULTIPARTY_NO;

		DBG("call %s direction %d multiparty %d", vc->number,
							direction, multiparty);

		telephony_list_current_call_ind(i, direction, vc->status,
					CALL_MODE_VOICE, multiparty,
					vc->number, number_type(vc->number));
	}

	telephony_list_current_calls_rsp(telephony_device, CME_ERROR_NONE);
}
