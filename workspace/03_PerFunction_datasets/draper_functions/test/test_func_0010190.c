language_select(ebmCallbackData *data)
{
	ebmContactData *ecd = (ebmContactData *)data;
	struct contact *cont;
	char buf[1024];

	cont = find_contact_by_nick(ecd->contact);

	if (cont == NULL) {
		return;
	}

	g_snprintf(buf, 1024,
		_("Select the code for the language to use when talking to %s"),
		cont->nick);

	do_list_dialog(buf, _("Select Language"), languages,
		&language_selected, (gpointer) cont);
}
