abort_pushes(WSPMachine *sm, long reason)
{
        WAPEvent *ab;
	WSPPushMachine *psm;
	long i, len;

        ab = wap_event_create(Abort_Event);
	ab->u.Abort_Event.reason = reason;

        len = gwlist_len(sm->pushmachines);
	for (i = len - 1; i >= 0; i--) {
		psm = gwlist_get(sm->pushmachines, i);
		handle_push_event(sm, psm, ab);
	}

        wap_event_destroy(ab);
}
