odf_write_bubble_series (GnmOOExport *state, GSList const *orig_series)
{
	GnmParsePos pp;
	int i, j;
	GSList const *series;
	parse_pos_init (&pp, WORKBOOK (state->wb), NULL, 0,0 );

	for (series = orig_series, i = 1; NULL != series; series = series->next, i++) {
		GOData const *dat = gog_dataset_get_dim (GOG_DATASET (series->data), 2);

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
				for (j = 1; j >= 0; j--) {
					dat = gog_dataset_get_dim (GOG_DATASET (series->data), j);
					if (NULL != dat) {
						texpr = gnm_go_data_get_expr (dat);
						if (NULL != texpr) {
							str = gnm_expr_top_as_string (texpr, &pp, state->conv);
							gsf_xml_out_start_element (state->xml, CHART "domain");
							gsf_xml_out_add_cstr (state->xml, TABLE "cell-range-address",
									      odf_strip_brackets (str));
							gsf_xml_out_end_element (state->xml);
							g_free (str);
						}
					}
				}
			}
			gsf_xml_out_end_element (state->xml);
		}
	}
}
