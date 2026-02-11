odf_write_gantt_series (GnmOOExport *state, GSList const *series)
{
	GnmParsePos pp;
	int i;
	parse_pos_init (&pp, WORKBOOK (state->wb), NULL, 0,0 );

	for (i = 1; NULL != series ; series = series->next, i++) {
		GOData const *dat = gog_dataset_get_dim (GOG_DATASET (series->data), GOG_MS_DIM_VALUES);
		if (NULL != dat) {
			GnmExprTop const *texpr = gnm_go_data_get_expr (dat);
			if (NULL != texpr) {
				char *str = gnm_expr_top_as_string (texpr, &pp, state->conv);
				GOData const *cat = gog_dataset_get_dim (GOG_DATASET (series->data), GOG_MS_DIM_LABELS);
				gsf_xml_out_start_element (state->xml, CHART "series");
				gsf_xml_out_add_cstr (state->xml, CHART "values-cell-range-address",
						      odf_strip_brackets (str));
				g_free (str);
				str = odf_get_gog_style_name_from_obj (series->data);
				gsf_xml_out_add_cstr (state->xml, CHART "style-name", str);
				g_free (str);
				if (NULL != cat) {
					texpr = gnm_go_data_get_expr (cat);
					if (NULL != texpr) {
						str = gnm_expr_top_as_string (texpr, &pp, state->conv);
						gsf_xml_out_start_element (state->xml, CHART "domain");
						gsf_xml_out_add_cstr (state->xml, TABLE "cell-range-address",
								      odf_strip_brackets (str));
						gsf_xml_out_end_element (state->xml);
						g_free (str);
					}
				}
				gsf_xml_out_end_element (state->xml);
			}
		}
		dat = gog_dataset_get_dim (GOG_DATASET (series->data), GOG_MS_DIM_CATEGORIES);
		if (NULL != dat) {
			GnmExprTop const *texpr = gnm_go_data_get_expr (dat);
			if (NULL != texpr) {
				char *str = gnm_expr_top_as_string (texpr, &pp, state->conv);
				gsf_xml_out_start_element (state->xml, CHART "series");
				gsf_xml_out_add_cstr (state->xml, CHART "values-cell-range-address",
						      odf_strip_brackets (str));
				g_free (str);
				str = odf_get_gog_style_name_from_obj (series->data);
				gsf_xml_out_add_cstr (state->xml, CHART "style-name", str);
				g_free (str);
				gsf_xml_out_end_element (state->xml);
			}
		}
	}
}
