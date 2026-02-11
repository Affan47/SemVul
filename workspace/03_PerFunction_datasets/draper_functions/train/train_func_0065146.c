xml_write_scenario (GnmOutputXML *state, GnmScenario const *sc)
{
	GSList *l;
	GnmParsePos pp;

	parse_pos_init_sheet (&pp, sc->sheet);

	gsf_xml_out_start_element (state->output, GNM "Scenario");

	gsf_xml_out_add_cstr (state->output, "Name", sc->name);
	if (sc->comment)
		gsf_xml_out_add_cstr (state->output, "Comment", sc->comment);

	for (l = sc->items; l; l = l->next) {
		GnmScenarioItem const *sci = l->data;
		GnmValue const *val = sci->value;
		GString *str;
		GnmConventionsOut out;

		if (!gnm_scenario_item_valid (sci, NULL))
			continue;

		str = g_string_new (NULL);
		gsf_xml_out_start_element (state->output, GNM "Item");

		out.accum = str;
		out.pp    = &pp;
		out.convs = state->convs;

		gnm_expr_top_as_gstring (sci->dep.texpr, &out);
		gsf_xml_out_add_cstr (state->output, "Range", str->str);

		if (val) {
			gsf_xml_out_add_int (state->output,
					     "ValueType",
					     val->type);
			if (VALUE_FMT (val) != NULL) {
				const char *fmt = go_format_as_XL (VALUE_FMT (val));
				gsf_xml_out_add_cstr (state->output, "ValueFormat", fmt);
			}
			g_string_truncate (str, 0);
			value_get_as_gstring (val, str, state->convs);
			gsf_xml_out_add_cstr (state->output, NULL, str->str);
		}

		gsf_xml_out_end_element (state->output);
		g_string_free (str, TRUE);
	}

	gsf_xml_out_end_element (state->output);
}
