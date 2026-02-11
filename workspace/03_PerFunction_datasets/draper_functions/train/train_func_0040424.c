xlsx_CT_FilterColumn_begin (GsfXMLIn *xin, xmlChar const **attrs)
{
	XLSXReadState *state = (XLSXReadState *)xin->user_state;
	int id = -1;
	gboolean hidden = FALSE;
	gboolean show = TRUE;

	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (attr_int  (xin, attrs, "colId", &id)) ;
		else if (attr_bool (xin, attrs, "hiddenButton", &hidden)) ;
		else if (attr_bool (xin, attrs, "showButton", &show)) ;

	state->filter_cur_field = id;
}
