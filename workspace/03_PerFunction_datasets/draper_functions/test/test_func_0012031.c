gnm_xml_finish_obj (GsfXMLIn *xin)
{
	XMLSaxParseState *state = (XMLSaxParseState *)xin->user_state;
	GnmCellRegion *cr = state->clipboard;

	if (cr) {
		cr->objects = g_slist_prepend (cr->objects, state->so);
	} else {
		sheet_object_set_sheet (state->so, state->sheet);
		g_object_unref (state->so);
	}

	state->so = NULL;
}
