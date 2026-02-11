xlsx_CT_WorkbookPr (GsfXMLIn *xin, xmlChar const **attrs)
{
	static EnumVal const switchModes[] = {
		{ "on",	 TRUE },
		{ "1",	 TRUE },
		{ "true", TRUE },
		{ "off", FALSE },
		{ "0", FALSE },
		{ "false", FALSE },
		{ NULL, 0 }
	};
	int tmp;
	XLSXReadState *state = (XLSXReadState *)xin->user_state;

	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (attr_enum (xin, attrs, "date1904", switchModes, &tmp))
			workbook_set_1904 (state->wb, tmp);
}
