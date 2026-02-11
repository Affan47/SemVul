alloc_named_ct(int *limit, Bool do_allocate)
{


	char *color_names[] =
	{
		"black",
		"white",
		"grey",
		"green",
		"blue",
		"red",
		"cyan",
		"yellow",
		"magenta",
		"DodgerBlue",
		"SteelBlue",
		"chartreuse",
		"wheat",
		"turquoise",
		"CadetBlue",
		"gray87",
		"CornflowerBlue",
		"YellowGreen",
		"NavyBlue",
		"MediumBlue",
		"plum",
		"aquamarine",
		"orchid",
		"ForestGreen",
		"lightyellow",
		"brown",
		"orange",
		"red3",
		"HotPink",
		"LightBlue",
		"gray47",
		"pink",
		"red4",
		"violet",
		"purple",
		"gray63",
		"gray94",
		"plum1",
		"PeachPuff",
		"maroon",
		"lavender",
		"salmon",
		"blue4",
		"PaleGreen4",
		"#AA7700",
		"#11EE88",
		"#884466",
		"#CC8888",
		"#EECC44",
		"#AAAA44",
		"#FF1188",
		"#992299",
		"#CCFFAA",
		"#664400",
		"#AADD99",
		"#66CCFF",
		"#CC2299",
		"#FF11CC",
		"#11CC99",
		"#AA77AA",
		"#EEBB77"
	};
	int NColors = sizeof(color_names)/sizeof(char *);
	int i,rc;
	PColor *color_table;
	XColor color;

	*limit = (*limit > NColors)? NColors: *limit;
	color_table = (PColor *)safemalloc((*limit+1) * sizeof(PColor));
	for(i=0; i<*limit; i++)
	{
		rc=XParseColor(Pdpy, Pcmap, color_names[i], &color);
		if (rc==0) {
			fprintf(stderr,"color_to_rgb: can't parse color %s,"
				" rc %d\n", color_names[i], rc);
			free_table_colors(color_table, i);
			free(color_table);
			return NULL;
		}
		if (do_allocate)
		{
			if (!XAllocColor(Pdpy, Pcmap, &color))
			{
				free_table_colors(color_table, i);
				free(color_table);
				return NULL;
			}
			color_table[i].color.pixel = color.pixel;
			color_table[i].alloc_count = 1;
		}
		else
		{
			color_table[i].alloc_count = 0;
		}
		color_table[i].color.red = color.red;
		color_table[i].color.green = color.green;
		color_table[i].color.blue = color.blue;
	}
	color_table[*limit].color.red = color_table[*limit-1].color.red;
	color_table[*limit].color.green = color_table[*limit-1].color.green;
	color_table[*limit].color.blue = color_table[*limit-1].color.blue;
	color_table[*limit].color.pixel = color_table[*limit-1].color.pixel;
	color_table[*limit].alloc_count = 0;
	PColorLimit = *limit;
	return color_table;
}
