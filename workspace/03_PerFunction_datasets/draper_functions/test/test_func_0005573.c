odf_write_gradient_info (GOStyle const *style, char const *name, GnmOOExport *state)
{
	char *color;
	char const *type = "linear";
	int angle = 0;
	struct {
		unsigned int dir;
		char const *type;
		int angle;
	} gradients[] = {
		{GO_GRADIENT_N_TO_S,"linear", 180},
		{GO_GRADIENT_S_TO_N, "linear", 0},
		{GO_GRADIENT_N_TO_S_MIRRORED, "axial", 180},
		{GO_GRADIENT_S_TO_N_MIRRORED, "axial", 0},
		{GO_GRADIENT_W_TO_E, "linear", -90},
		{GO_GRADIENT_E_TO_W, "linear", 90},
		{GO_GRADIENT_W_TO_E_MIRRORED, "axial", -90},
		{GO_GRADIENT_E_TO_W_MIRRORED, "axial", 90},
		{GO_GRADIENT_NW_TO_SE, "linear", -135},
		{GO_GRADIENT_SE_TO_NW, "linear", 45},
		{GO_GRADIENT_NW_TO_SE_MIRRORED, "axial", -135 },
		{GO_GRADIENT_SE_TO_NW_MIRRORED, "axial", 45},
		{GO_GRADIENT_NE_TO_SW, "linear", 135},
		{GO_GRADIENT_SW_TO_NE, "linear", -45},
		{GO_GRADIENT_SW_TO_NE_MIRRORED, "axial", -45},
		{GO_GRADIENT_NE_TO_SW_MIRRORED, "axial", 135},
	};
	int i;

	gsf_xml_out_start_element (state->xml, DRAW "gradient");
	gsf_xml_out_add_cstr_unchecked (state->xml, DRAW "name", name);

	color = odf_go_color_to_string (style->fill.pattern.back);
	gsf_xml_out_add_cstr_unchecked (state->xml, DRAW "start-color", color);
	g_free (color);

	if (style->fill.gradient.brightness >= 0.0 && state->with_extension)
		gsf_xml_out_add_float (state->xml, GNMSTYLE "brightness",
				       style->fill.gradient.brightness, -1);

	color = odf_go_color_to_string (style->fill.pattern.fore);
	gsf_xml_out_add_cstr_unchecked (state->xml, DRAW "end-color", color);
	g_free (color);

	for (i = 0; i < (int)G_N_ELEMENTS (gradients); i++) {
		if (gradients[i].dir == style->fill.gradient.dir) {
			type = gradients[i].type;
			angle = gradients[i].angle;
			break;
		}
	}
	gsf_xml_out_add_cstr_unchecked (state->xml, DRAW "style", type);
	gsf_xml_out_add_int (state->xml, DRAW "angle", angle);

	gsf_xml_out_end_element (state->xml);
}
