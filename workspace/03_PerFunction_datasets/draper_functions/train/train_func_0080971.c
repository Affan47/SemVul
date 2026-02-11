PictureReduceColorName(char **my_color)
{
	int index;
	XColor rgb;

	if (!XpmSupport)
		return;

	if (!strcasecmp(*my_color,"none")) {
		return;
	}

	if (!XParseColor(Pdpy, Pcmap, *my_color, &rgb))
	{
		fprintf(stderr,"color_to_rgb: can't parse color %s\n",
			*my_color);
	}
	index = get_color_index(rgb.red,rgb.green,rgb.blue, False);


	free(*my_color);

	*my_color = safemalloc(8);
	sprintf(*my_color,"#%x%x%x",
		Pct[index].color.red >> 8,
		Pct[index].color.green >> 8,
		Pct[index].color.blue >> 8);
	return;
}
