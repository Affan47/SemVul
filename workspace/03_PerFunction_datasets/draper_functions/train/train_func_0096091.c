odf_write_axis_categories (GnmOOExport *state, GSList const *series)
{
	if (series != NULL && series->data != NULL) {
		GOData const *cat = gog_dataset_get_dim (GOG_DATASET (series->data), GOG_MS_DIM_LABELS);
		if (NULL != cat) {
			GnmExprTop const *texpr = gnm_go_data_get_expr (cat);
			if (NULL != texpr) {
				char *cra;
				GnmParsePos pp;
				parse_pos_init (&pp, WORKBOOK (state->wb), NULL, 0,0 );
				cra = gnm_expr_top_as_string (texpr, &pp, state->conv);

				gsf_xml_out_start_element (state->xml, CHART "categories");
				gsf_xml_out_add_cstr (state->xml, TABLE "cell-range-address",
						      odf_strip_brackets (cra));
				gsf_xml_out_end_element (state->xml);

				g_free (cra);
			}
		}
	}
}
