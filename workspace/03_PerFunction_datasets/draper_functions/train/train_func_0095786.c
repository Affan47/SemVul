action_list_cards (GSList *contacts,
                   ActionContext *p_actctx)
{
	FILE *outputfile;
	long length;
	CARD_FORMAT format;

	length = g_slist_length (contacts);

	if (length <= 0) {
		g_warning ("Couldn't load addressbook correctly!!!! %s####", p_actctx->addressbook_source_uid ?
				p_actctx->addressbook_source_uid : "NULL");
		exit (-1);
	}

	if (p_actctx->output_file == NULL) {
		outputfile = stdout;
	} else {

		if (!(outputfile = g_fopen (p_actctx->output_file, "w"))) {
			g_warning (_("Can not open file"));
			exit (-1);
		}
	}

	if (p_actctx->IsVCard == TRUE)
		format = CARD_FORMAT_VCARD;
	else
		format = CARD_FORMAT_CSV;

	output_n_cards_file (outputfile, contacts, length, 0, format);

	if (p_actctx->output_file != NULL) {
		fclose (outputfile);
	}
}
