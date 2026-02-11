find_color(struct high_color *colors,unsigned char *name,unsigned char *syn)
{
	unsigned char bf[256];
	struct high_color *color;
	joe_snprintf_2(bf, sizeof(bf), "%s.%s", syn, name);
	for (color = colors; color; color = color->next)
		if (!zcmp(color->name,bf)) break;
	if (color)
		return color;
	for (color = colors; color; color = color->next)
		if (!zcmp(color->name,name)) break;
	return color;
}
