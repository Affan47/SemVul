xml_sax_selection (GsfXMLIn *xin, xmlChar const **attrs)
{
	XMLSaxParseState *state = (XMLSaxParseState *)xin->user_state;
	Sheet *sheet = xml_sax_must_have_sheet (state);
	int col = -1, row = -1;

	sv_selection_reset (sheet_get_view (sheet, state->wb_view));

	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (gnm_xml_attr_int (attrs, "CursorCol", &col)) ;
		else if (gnm_xml_attr_int (attrs, "CursorRow", &row)) ;
		else
			unknown_attr (xin, attrs);

	XML_CHECK (state->cell.col < 0);
	XML_CHECK (state->cell.row < 0);


	state->cell.col = 0;
	state->cell.row = 0;

	XML_CHECK (col >= 0 && col < gnm_sheet_get_max_cols (sheet));
	XML_CHECK (row >= 0 && row < gnm_sheet_get_max_rows (sheet));

	state->cell.col = col;
	state->cell.row = row;
}
