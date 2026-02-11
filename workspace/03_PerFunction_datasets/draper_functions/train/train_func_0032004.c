parse_name_for_stretch (char const *cc)
{
	g_assert ( cc != NULL );
	gchar *c = g_ascii_strdown (cc, -1);

	gint stretch;
	if (strstr (c, "ultra narrow") || strstr (c, "ultra condensed") || strstr (c, "extra condensed")) {
		stretch = NR_POS_STRETCH_EXTRA_CONDENSED;
	} else if (strstr (c, "ultra wide") || strstr (c, "ultra expanded") || strstr (c, "ultra extended")  || strstr (c, "extra expanded")) {
		stretch = NR_POS_STRETCH_EXTRA_EXPANDED;
	} else if (strstr (c, "semi condensed") || strstr (c, "semicondensed")) {
		stretch = NR_POS_STRETCH_SEMI_CONDENSED;
	} else if (strstr (c, "semi extended") || strstr (c, "semiextended")) {
		stretch = NR_POS_STRETCH_SEMI_EXPANDED;
	} else if (strstr (c, "narrow") || strstr (c, "condensed")) {
		stretch = NR_POS_STRETCH_CONDENSED;
	} else if (strstr (c, "wide") || strstr (c, "expanded") || strstr (c, "extended")) {
		stretch = NR_POS_STRETCH_EXPANDED;
	} else {
		stretch = NR_POS_STRETCH_NORMAL;
	}

	g_free (c);
	return stretch;
}
