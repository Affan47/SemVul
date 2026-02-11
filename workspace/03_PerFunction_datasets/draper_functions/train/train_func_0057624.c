squelch_sval_menu_action(menu_type *m, const ui_event *event,
		int oid)
{
	const squelch_choice *choice = menu_priv(m);

	if (event->type == EVT_SELECT)
	{
		object_kind *kind = choice[oid].kind;


		if (choice[oid].aware)
			kind->squelch ^= SQUELCH_IF_AWARE;
		else
			kind->squelch ^= SQUELCH_IF_UNAWARE;

		p_ptr->notice |= PN_SQUELCH;
		return TRUE;
	}

	return FALSE;
}
