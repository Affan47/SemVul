ssindex_hlink (IndexerState *state, GnmHLink const *lnk)
{
	gchar const *str;

	str = gnm_hlink_get_target (lnk);
	if (str)
		gsf_xml_out_simple_element (state->output, "data", str);

	str = gnm_hlink_get_tip (lnk);
	if (str)
		gsf_xml_out_simple_element (state->output, "data", str);
}
