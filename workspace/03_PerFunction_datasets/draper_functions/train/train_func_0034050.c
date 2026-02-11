cr_style_resolve_inherited_properties (CRStyle *a_this)
{
	enum CRStatus ret = CR_OK;
	glong i = 0;

	g_return_val_if_fail (a_this, CR_BAD_PARAM_ERROR);
	g_return_val_if_fail (a_this->parent_style, CR_BAD_PARAM_ERROR) ;

        if (a_this->inherited_props_resolved == TRUE)
                return CR_OK ;

        for (i=0 ; i < NB_NUM_PROPS ;i++) {
                if (a_this->num_props[i].sv.type == NUM_INHERIT) {
                        cr_num_copy (&a_this->num_props[i].cv,
                                     &a_this->parent_style->num_props[i].cv);
                }
        }
	for (i=0; i < NB_RGB_PROPS; i++) {
		if (cr_rgb_is_set_to_inherit (&a_this->rgb_props[i].sv) == TRUE) {
			cr_rgb_copy (
				&a_this->rgb_props[i].cv,
				&a_this->parent_style->rgb_props[i].cv);
		}
	}
	for (i = 0; i < NB_BORDER_STYLE_PROPS; i++) {
		if (a_this->border_style_props[i] == BORDER_STYLE_INHERIT) {
			a_this->border_style_props[i] =
			  a_this->parent_style->border_style_props[i];
		}
	}

	if (a_this->display == DISPLAY_INHERIT) {
		a_this->display = a_this->parent_style->display;
	}
	if (a_this->position == POSITION_INHERIT) {
		a_this->position = a_this->parent_style->position;
	}
	if (a_this->float_type == FLOAT_INHERIT) {
		a_this->float_type = a_this->parent_style->float_type;
	}
	if (a_this->font_style == FONT_STYLE_INHERIT) {
		a_this->font_style = a_this->parent_style->font_style;
	}
	if (a_this->font_variant == FONT_VARIANT_INHERIT) {
		a_this->font_variant = a_this->parent_style->font_variant;
	}
	if (a_this->font_weight == FONT_WEIGHT_INHERIT) {
		a_this->font_weight = a_this->parent_style->font_weight;
	}
	if (a_this->font_stretch == FONT_STRETCH_INHERIT) {
		a_this->font_stretch = a_this->parent_style->font_stretch;
	}

	if (a_this->font_family == NULL)  {
		a_this->font_family = a_this->parent_style->font_family;
	}
        if (a_this->font_size.sv.type == INHERITED_FONT_SIZE) {
                cr_font_size_copy (&a_this->font_size.cv,
                                   &a_this->parent_style->font_size.cv) ;
        }
        a_this->inherited_props_resolved = TRUE ;
	return ret;
}
