odf_write_axis_full (GnmOOExport *state,
		     GogObject const *chart,
		     char const *axis_role,
		     char const *style_label,
		     char const *dimension,
		     G_GNUC_UNUSED odf_chart_type_t gtype,
		     GSList const *series,
		     gboolean include_cats)
{
	GogObject const *axis;

	if (axis_role == NULL)
		return;

	axis = gog_object_get_child_by_name (chart, axis_role);
	if (axis != NULL) {
		gsf_xml_out_start_element (state->xml, CHART "axis");
		gsf_xml_out_add_cstr (state->xml, CHART "dimension", dimension);
		gsf_xml_out_add_cstr (state->xml, CHART "style-name", style_label);
		odf_write_label (state, axis);
		odf_write_axis_grid (state, axis);
		if (include_cats)
			odf_write_axis_categories (state, series);
		gsf_xml_out_end_element (state->xml);
	}

}
