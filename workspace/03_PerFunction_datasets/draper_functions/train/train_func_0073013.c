sheet_cell_set_text (GnmCell *cell, char const *text, PangoAttrList *markup)
{
	GnmExprTop const *texpr;
	GnmValue *val;
	GnmParsePos pp;

	g_return_if_fail (cell != NULL);
	g_return_if_fail (text != NULL);
	g_return_if_fail (!gnm_cell_is_nonsingleton_array (cell));

	parse_text_value_or_expr (parse_pos_init_cell (&pp, cell),
		text, &val, &texpr);


	sheet_redraw_cell (cell);

	if (texpr != NULL) {
		gnm_cell_set_expr (cell, texpr);
		gnm_expr_top_unref (texpr);


		cell_queue_recalc (cell);


		sheet_cell_calc_span (cell, GNM_SPANCALC_SIMPLE);
	} else {
		g_return_if_fail (val != NULL);

		gnm_cell_set_value (cell, val);
		if (markup != NULL && VALUE_IS_STRING (cell->value)) {
			gboolean quoted = (text[0] == '\'');
			PangoAttrList *adj_markup;
			GOFormat *fmt;

			if (quoted) {

				adj_markup = pango_attr_list_copy (markup);
				go_pango_attr_list_erase (adj_markup, 0, 1);
			} else
				adj_markup = markup;

			fmt = go_format_new_markup (adj_markup, TRUE);
			value_set_fmt (cell->value, fmt);
			go_format_unref (fmt);
			if (quoted)
				pango_attr_list_unref (adj_markup);
		}


		cell_queue_recalc (cell);

		sheet_cell_calc_span (cell, GNM_SPANCALC_RESIZE | GNM_SPANCALC_RENDER);
	}

	sheet_flag_status_update_cell (cell);
}
