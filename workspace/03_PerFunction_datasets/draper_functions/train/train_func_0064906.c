GMT_getpen (char *buffer, struct GMT_PEN *P)
{
	GMT_LONG i, n, pen_unit = GMT_PT;
	double pen_scale = 1.0;
	char pen[GMT_LONG_TEXT], color[GMT_LONG_TEXT], texture[GMT_LONG_TEXT], line[BUFSIZ];

	strcpy (line, buffer);
	GMT_chop (line);
	if (!strchr (line, ',')) {
		GMT_old2newpen (line);
	}


	memset ((void *)pen, 0, (size_t)(GMT_LONG_TEXT*sizeof(char)));
	memset ((void *)color, 0, (size_t)(GMT_LONG_TEXT*sizeof(char)));
	memset ((void *)texture, 0, (size_t)(GMT_LONG_TEXT*sizeof(char)));
	for (i = 0; line[i]; i++) if (line[i] == ',') line[i] = ' ';
	n = sscanf (line, "%s %s %s", pen, color, texture);
	for (i = 0; line[i]; i++) if (line[i] == ' ') line[i] = ',';
	if (n == 2) {
		if (line[0] == ',' || (GMT_is_color(pen,3) && GMT_is_texture(color))) {
			strcpy (texture, color);
			strcpy (color, pen);
			pen[0] = '\0';
		}
		else if ((GMT_is_penwidth(pen) && GMT_is_texture(color))) {
			strcpy (texture, color);
			color[0] = '\0';
		}
		else if (strstr(line, ",,") || GMT_is_texture(color)) {
			strcpy (texture, color);
			color[0] = '\0';
		}

	}
	else if (n == 1) {
		if (strstr (line, ",,") || GMT_is_texture (line)) {
			strcpy (texture, pen);
			pen[0] = color[0] = '\0';
		}
		else if (line[0] == ',' || GMT_is_color(line,3)) {
			strcpy (color, pen);
			pen[0] = '\0';
		}

	}


	GMT_init_pen (P, GMT_PENWIDTH);

	GMT_getpenwidth (pen, &pen_unit, &pen_scale, P);
	GMT_getrgb (color, P->rgb);
	GMT_gettexture (texture, pen_unit, pen_scale, P);

	return (P->width < 0.0 || GMT_check_rgb (P->rgb));
}
