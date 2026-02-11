svg_parse_points(GF_List *values, char *value_string)
{
	u32 i = 0, j;
	char *str = value_string;
	u32 len = strlen(str);
	while (i < len) {
		SVG_Point *p;
		GF_SAFEALLOC(p, SVG_Point)
		j = svg_parse_point(p, &str[i]);
		if (j == 0) {


			while (gf_list_count(values)) {
				p = (SVG_Point *)gf_list_get(values, 0);
				gf_free(p);
				gf_list_rem(values, 0);
			}
			return;
		}
		i += j;
		gf_list_add(values, p);
	}
}
