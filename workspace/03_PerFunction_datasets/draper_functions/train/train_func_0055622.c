xl_xml_data_end (GsfXMLIn *xin, G_GNUC_UNUSED GsfXMLBlob *blob)
{
	ExcelXMLReadState *state = (ExcelXMLReadState *)xin->user_state;
	GnmCell *cell = sheet_cell_fetch (state->sheet, state->pos.col, state->pos.row);
	GnmValue *v;

	if (state->val_type == VALUE_FAKE_DATETIME) {
		GDate date;
		unsigned y, mo, d, h, mi;
		double s;
		if (6 == sscanf (xin->content->str, "%u-%u-%uT%u:%u:%lg", &y, &mo, &d, &h, &mi, &s)) {
			g_date_clear (&date, 1);
			g_date_set_dmy (&date, d, mo, y);
			if (g_date_valid (&date)) {
				unsigned d_serial = go_date_g_to_serial (&date,
					workbook_date_conv (state->wb));
				v = value_new_float (d_serial + h/24. + mi/(24.*60.) + s/(24.*60.*60.));
			} else
				v = value_new_string (xin->content->str);
		} else
			v = value_new_string (xin->content->str);
	} else if (state->val_type == VALUE_FLOAT) {
			char *end;
			v  = value_new_float (gnm_strto (xin->content->str, &end));
			if (*end)
				xl_xml_warning
					(xin, _("Invalid content of ss:data "
						"element, expected number, "
						"received '%s'"),
					 xin->content->str);
	} else
		v = value_new_from_string (state->val_type, xin->content->str,
					   NULL, FALSE);
	if (NULL != state->texpr) {
		if (NULL != v)
			gnm_cell_set_expr_and_value (cell, state->texpr, v, TRUE);
		else
			gnm_cell_set_expr (cell, state->texpr);
		gnm_expr_top_unref (state->texpr);
		state->texpr = NULL;
	} else if (NULL != v)
		gnm_cell_set_value (cell, v);
	else {
		gnm_cell_set_text (cell, xin->content->str);
		xl_xml_warning
			(xin, _("Invalid content of ss:data "
				"element, received '%s'"),
			 xin->content->str);
	}
}
