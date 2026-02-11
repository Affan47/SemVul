vlines_set_attrb(const struct GParams *params)
{
    int i, color, width, flat, height;
    int *vect_list, nvects;

    vect_list = GV_get_vect_list(&nvects);

    for (i = 0; i < nvects; i++) {

	color = Nviz_color_from_str(params->vline_color->answers[i]);
	width = atoi(params->vline_width->answers[i]);
	if (strcmp(params->vline_mode->answers[i], "flat") == 0)
	    flat = 1;
	else
	    flat = 0;
	if (GV_set_vectmode(vect_list[i], 1, color, width, flat) < 0)
	    return 0;


	height = atoi(params->vline_height->answers[i]);
	if (height > 0)
	    GV_set_trans(vect_list[i], 0.0, 0.0, height);
    }

    return 1;
}
