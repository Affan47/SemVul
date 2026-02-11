xml_write_scenarios (GnmOutputXML *state)
{
	GList *ptr;

	if (state->sheet->scenarios == NULL)
		return;

	gsf_xml_out_start_element (state->output, GNM "Scenarios");

	for (ptr = state->sheet->scenarios ; ptr != NULL ; ptr = ptr->next) {
		GnmScenario const *sc = ptr->data;
		xml_write_scenario (state, sc);
	}

	gsf_xml_out_end_element (state->output);
}
