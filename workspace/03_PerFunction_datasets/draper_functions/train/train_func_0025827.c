odf_write_one_axis_grid (GnmOOExport *state, GogObject const *axis,
			 char const *role, char const *class)
{
	GogObject const *grid;

	grid = gog_object_get_child_by_name (axis, role);
	if (grid) {
		char *style = odf_get_gog_style_name_from_obj (GOG_OBJECT (grid));

		gsf_xml_out_start_element (state->xml, CHART "grid");
		gsf_xml_out_add_cstr (state->xml, CHART "style-name", style);
		gsf_xml_out_add_cstr (state->xml, CHART "class", class);
		gsf_xml_out_end_element (state->xml);

		g_free (style);
	}
}
