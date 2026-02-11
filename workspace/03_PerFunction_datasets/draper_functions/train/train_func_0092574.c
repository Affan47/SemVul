output_n_cards_file (FILE *outputfile,
                     GSList *contacts,
                     gint size,
                     gint begin_no,
                     CARD_FORMAT format)
{
	gint i;
	if (format == CARD_FORMAT_VCARD) {
		for (i = begin_no; i < size + begin_no; i++) {
			EContact *contact = g_slist_nth_data (contacts, i);
			gchar *vcard = e_vcard_to_string (E_VCARD (contact), EVC_FORMAT_VCARD_30);
			fprintf (outputfile, "%s\n", vcard);
			g_free (vcard);
		}
	} else if (format == CARD_FORMAT_CSV) {
		gchar *csv_fields_name;

		if (!pre_defined_fields)
			set_pre_defined_field (&pre_defined_fields);

		csv_fields_name = e_contact_csv_get_header_line (pre_defined_fields);
		fprintf (outputfile, "%s\n", csv_fields_name);
		g_free (csv_fields_name);

		for (i = begin_no; i < size + begin_no; i++) {
			EContact *contact = g_slist_nth_data (contacts, i);
			gchar *csv = e_contact_get_csv (contact, pre_defined_fields);
			fprintf (outputfile, "%s\n", csv);
			g_free (csv);
		}
	}

	return SUCCESS;

}
