gg_svg_split_css_token (struct gg_svg_style *style, char *value)
{

    char *p = value;
    char *p_value = NULL;
    while (*p != '\0')
      {
	  if (*p == ':')
	    {
		*p = '\0';
		p_value = p + 1;
		break;
	    }
	  p++;
      }
    if (p_value == NULL)
	return;
    if (strcmp (value, "opacity") == 0)
	gg_svg_parse_opacity (style, p_value);
    else if (strcmp (value, "stroke") == 0)
	gg_svg_parse_stroke_color (style, p_value);
    else if (strcmp (value, "stroke-width") == 0)
	gg_svg_parse_stroke_width (style, p_value);
    else if (strcmp (value, "stroke-linecap") == 0)
	gg_svg_parse_stroke_linecap (style, p_value);
    else if (strcmp (value, "stroke-linejoin") == 0)
	gg_svg_parse_stroke_linejoin (style, p_value);
    else if (strcmp (value, "stroke-miterlimit") == 0)
	gg_svg_parse_stroke_miterlimit (style, p_value);
    else if (strcmp (value, "stroke-dasharray") == 0)
	gg_svg_parse_stroke_dasharray (style, p_value);
    else if (strcmp (value, "stroke-dashoffset") == 0)
	gg_svg_parse_stroke_dashoffset (style, p_value);
    else if (strcmp (value, "stroke-opacity") == 0)
	gg_svg_parse_stroke_opacity (style, p_value);
    else if (strcmp (value, "fill") == 0)
	gg_svg_parse_fill_color (style, p_value);
    else if (strcmp (value, "fill-rule") == 0)
	gg_svg_parse_fill_rule (style, p_value);
    else if (strcmp (value, "fill-opacity") == 0)
	gg_svg_parse_fill_opacity (style, p_value);
    else if (strcmp (value, "display") == 0)
	gg_svg_parse_display (style, p_value);
    else if (strcmp (value, "visibility") == 0)
	gg_svg_parse_visibility (style, p_value);
}
