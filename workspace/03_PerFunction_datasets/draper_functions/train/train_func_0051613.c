gg_svg_parse_fill_color (struct gg_svg_style *style, const char *color)
{

    int len = strlen (color);
    char buf[16];
    const char *p_color = NULL;
    if (strcmp (color, "none") == 0)
      {
	  style->no_fill = 1;
	  return;
      }
    if (gg_svg_parse_fill_gradient_url (style, color) == 1)
	return;
    style->fill = 1;
    if (*color == '#' && len >= 7)
	p_color = color;
    else if (*color == '#' && len == 4)
      {
	  buf[0] = *(color + 0);
	  buf[1] = *(color + 1);
	  buf[2] = *(color + 1);
	  buf[3] = *(color + 2);
	  buf[4] = *(color + 2);
	  buf[5] = *(color + 3);
	  buf[6] = *(color + 3);
	  p_color = buf;
      }
    else
      {
	  gg_svg_from_named_color (buf, color);
	  if (*buf != '\0')
	      p_color = buf;
	  else
	      p_color = NULL;
      }
    if (p_color == NULL)
	p_color = "#000000";
    style->fill_red = gg_svg_parse_hex_color (*(p_color + 1), *(p_color + 2));
    style->fill_green = gg_svg_parse_hex_color (*(p_color + 3), *(p_color + 4));
    style->fill_blue = gg_svg_parse_hex_color (*(p_color + 5), *(p_color + 6));
}
