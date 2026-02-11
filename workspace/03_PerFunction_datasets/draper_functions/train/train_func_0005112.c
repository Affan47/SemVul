main_thread(void *arg) {
	WAPEvent *e;
	WSPMachine *sm;
	WSP_PDU *pdu;

	while (run_status == running && (e = gwlist_consume(queue)) != NULL) {
		wap_event_assert(e);
		switch (e->type) {
		case TR_Invoke_Ind:
			pdu = wsp_pdu_unpack(e->u.TR_Invoke_Ind.user_data);
			if (pdu == NULL) {
				warning(0, "WSP: Broken PDU ignored.");
				wap_event_destroy(e);
				continue;
			}
			break;

		default:
			pdu = NULL;
			break;
		}

		sm = find_session_machine(e, pdu);
		if (sm == NULL) {
			wap_event_destroy(e);
		} else {
			handle_session_event(sm, e, pdu);
		}

		wsp_pdu_destroy(pdu);
	}
}
