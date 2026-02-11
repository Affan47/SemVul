parse_name_for_weight (char const *cc)
{
	g_assert ( cc != NULL );
	gchar *c = g_ascii_strdown (cc, -1);

	gint weight;
	if (strstr (c, "thin")) {
		weight = NR_POS_WEIGHT_THIN;
	} else if (strstr (c, "extra light")) {
		weight = NR_POS_WEIGHT_EXTRA_LIGHT;
	} else if (strstr (c, "ultra light")) {
		weight = NR_POS_WEIGHT_ULTRA_LIGHT;
	} else if (strstr (c, "light")) {
		weight = NR_POS_WEIGHT_LIGHT;
	} else if (strstr (c, "book")) {
		weight = NR_POS_WEIGHT_BOOK;
	} else if (strstr (c, "medium")) {
		weight = NR_POS_WEIGHT_MEDIUM;
	} else if (strstr (c, "semi bold")) {
		weight = NR_POS_WEIGHT_SEMIBOLD;
	} else if (strstr (c, "semibold")) {
		weight = NR_POS_WEIGHT_SEMIBOLD;
	} else if (strstr (c, "demi bold")) {
		weight = NR_POS_WEIGHT_DEMIBOLD;
	} else if (strstr (c, "demibold") || strstr (c, "demi")) {
		weight = NR_POS_WEIGHT_DEMIBOLD;
	} else if (strstr (c, "ultra bold")) {
		weight = NR_POS_WEIGHT_ULTRA_BOLD;
	} else if (strstr (c, "extra bold") || strstr (c, "xbold") || strstr (c, "xtrabold")) {
		weight = NR_POS_WEIGHT_EXTRA_BOLD;
	} else if (strstr (c, "black") || strstr (c, "heavy")) {
		weight = NR_POS_WEIGHT_BLACK;
	} else if (strstr (c, "bold")) {

		weight = NR_POS_WEIGHT_BOLD;
	} else {
		weight = NR_POS_WEIGHT_NORMAL;
	}

	g_free (c);
	return weight;
}
