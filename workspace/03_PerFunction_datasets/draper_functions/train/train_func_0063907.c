tilda_expand(property_t prop)
{
    char *pathname;

	pathname = gnet_prop_get_string(prop, NULL, 0);

	if (NULL == pathname)
		return;

	if (0 == strcmp(pathname, "~")) {
		gnet_prop_set_string(prop, gethomedir());
	} else if (
		is_strprefix(pathname, "~/") ||
		is_strprefix(pathname, "~" G_DIR_SEPARATOR_S)
	) {
		const char *home = gethomedir();
		char *expanded;

		expanded = h_strconcat(home,
			'/' == pathname[1] ? "/" : G_DIR_SEPARATOR_S,
			&pathname[2], (void *) 0);

		gnet_prop_set_string(prop, expanded);
		HFREE_NULL(expanded);
	}


	if (is_running_on_mingw()) {
		char *patched;

		pathname = gnet_prop_get_string(prop, NULL, 0);
		patched = mingw_patch_personal_path(pathname);
		if (patched != pathname) {
			gnet_prop_set_string(prop, patched);
			HFREE_NULL(patched);
		}
	}
}
