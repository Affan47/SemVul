xlsx_CT_Top10 (GsfXMLIn *xin, xmlChar const **attrs)
{
	XLSXReadState *state = (XLSXReadState *)xin->user_state;
	gboolean top = TRUE;
	gboolean percent = FALSE;
	gnm_float val = -1.;
	GnmFilterCondition *cond;

	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (attr_float (xin, attrs, "val", &val)) ;
		else if (attr_bool (xin, attrs, "top", &top)) ;
		else if (attr_bool (xin, attrs, "percent", &percent)) ;

	if (NULL != (cond = gnm_filter_condition_new_bucket (top, !percent, FALSE, val)))
		gnm_filter_set_condition (state->filter, state->filter_cur_field,
			cond, FALSE);
}
