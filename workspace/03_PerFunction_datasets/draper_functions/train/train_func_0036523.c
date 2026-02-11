enq_ta(XtActionProc fn, char *parm1, char *parm2)
{
	struct ta *ta;


	if (!CONNECTED) {
		trace_event("  dropped (not connected)\n");
		return;
	}


	if (kybdlock & KL_OERR_MASK) {
		ring_bell();
		trace_event("  dropped (operator error)\n");
		return;
	}


	if (kybdlock & KL_SCROLLED) {
		ring_bell();
		trace_event("  dropped (scrolled)\n");
		return;
	}


	if (!appres.typeahead) {
		trace_event("  dropped (no typeahead)\n");
		return;
	}

	ta = (struct ta *) Malloc(sizeof(*ta));
	ta->next = (struct ta *) NULL;
	ta->fn = fn;
	ta->parm1 = ta->parm2 = CN;
	if (parm1) {
		ta->parm1 = NewString(parm1);
		if (parm2)
			ta->parm2 = NewString(parm2);
	}
	if (ta_head)
		ta_tail->next = ta;
	else {
		ta_head = ta;
		status_typeahead(True);
	}
	ta_tail = ta;

	trace_event("  action queued (kybdlock 0x%x)\n", kybdlock);
}
