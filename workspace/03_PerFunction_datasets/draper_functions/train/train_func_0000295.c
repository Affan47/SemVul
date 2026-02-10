xlsx_find_border (GnmStyle const *style, GPtrArray  *styles)
{
	unsigned i;
	for (i = 0 ; i < styles->len ; i++) {
		GnmStyle const *old_style = g_ptr_array_index (styles, i);
		if (style == old_style)
			return (gint) i;
		if (gnm_style_is_element_set (style, MSTYLE_BORDER_TOP) !=
		    gnm_style_is_element_set (old_style, MSTYLE_BORDER_TOP) ||
		    gnm_style_is_element_set (style, MSTYLE_BORDER_BOTTOM) !=
		    gnm_style_is_element_set (old_style, MSTYLE_BORDER_BOTTOM) ||
		    gnm_style_is_element_set (style, MSTYLE_BORDER_LEFT) !=
		    gnm_style_is_element_set (old_style, MSTYLE_BORDER_LEFT) ||
		    gnm_style_is_element_set (style, MSTYLE_BORDER_RIGHT) !=
		    gnm_style_is_element_set (old_style, MSTYLE_BORDER_RIGHT) ||
		    gnm_style_is_element_set (style, MSTYLE_BORDER_REV_DIAGONAL) !=
		    gnm_style_is_element_set (old_style, MSTYLE_BORDER_REV_DIAGONAL) ||
		    gnm_style_is_element_set (style, MSTYLE_BORDER_DIAGONAL) !=
		    gnm_style_is_element_set (old_style, MSTYLE_BORDER_DIAGONAL))
			continue;
		if (gnm_style_get_border (style, MSTYLE_BORDER_TOP)
		    != gnm_style_get_border (old_style, MSTYLE_BORDER_TOP) ||
		    gnm_style_get_border (style, MSTYLE_BORDER_BOTTOM)
		    != gnm_style_get_border (old_style, MSTYLE_BORDER_BOTTOM) ||
		    gnm_style_get_border (style, MSTYLE_BORDER_LEFT)
		    != gnm_style_get_border (old_style, MSTYLE_BORDER_LEFT) ||
		    gnm_style_get_border (style, MSTYLE_BORDER_RIGHT)
		    != gnm_style_get_border (old_style, MSTYLE_BORDER_RIGHT) ||
		    gnm_style_get_border (style, MSTYLE_BORDER_REV_DIAGONAL)
		    != gnm_style_get_border (old_style, MSTYLE_BORDER_REV_DIAGONAL) ||
		    gnm_style_get_border (style, MSTYLE_BORDER_DIAGONAL)
		    != gnm_style_get_border (old_style, MSTYLE_BORDER_DIAGONAL))
			continue;
		return (gint) i;
	}
	return -1;
}
