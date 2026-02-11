update_rgb_color(GtkColorComponentPrivate *ns, Color *c){
	switch (ns->component) {
		case rgb:
			color_copy(&ns->color, c);
			color_rgb_normalize(c);
			break;
		case hsv:
			color_hsv_to_rgb(&ns->color, c);
			color_rgb_normalize(c);
			break;
		case hsl:
			color_hsl_to_rgb(&ns->color, c);
			color_rgb_normalize(c);
			break;
		case cmyk:
			color_cmyk_to_rgb(&ns->color, c);
			color_rgb_normalize(c);
			break;
		case lab:
			{
				matrix3x3 adaptation_matrix;
				color_get_chromatic_adaptation_matrix(color_get_reference(ns->lab_illuminant, ns->lab_observer), color_get_reference(REFERENCE_ILLUMINANT_D65, REFERENCE_OBSERVER_2), &adaptation_matrix);
				color_lab_to_rgb(&ns->color, c, color_get_reference(ns->lab_illuminant, ns->lab_observer), color_get_inverted_sRGB_transformation_matrix(), &adaptation_matrix);
				color_rgb_normalize(c);
			}
			break;
		case xyz:

			break;
		case lch:
			{
				matrix3x3 adaptation_matrix;
				color_get_chromatic_adaptation_matrix(color_get_reference(ns->lab_illuminant, ns->lab_observer), color_get_reference(REFERENCE_ILLUMINANT_D65, REFERENCE_OBSERVER_2), &adaptation_matrix);
				color_lch_to_rgb(&ns->color, c, color_get_reference(ns->lab_illuminant, ns->lab_observer), color_get_inverted_sRGB_transformation_matrix(), &adaptation_matrix);
				color_rgb_normalize(c);
			}
			break;

	}
}
