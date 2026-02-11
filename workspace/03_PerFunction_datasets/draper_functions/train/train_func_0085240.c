theme_generator_adding(const char *text, int len, const char *dname, int themes_only)
{
	struct dirent **namelist = NULL;
	int count, i;

	count = scandir((dname) ? dname : ".", &namelist, NULL, alphasort);

	for(i = 0; i < count; i++) {
		struct stat st;
		char *name = namelist[i]->d_name, *tmp = saprintf("%s/%s", (dname) ? dname : "", name), *tmp2;

		if (!stat(tmp, &st)) {
			if (S_ISDIR(st.st_mode) && stat(saprintf("%s%s%s", tmp, "/", name), &st) == -1 && stat(saprintf("%s%s%s.theme", tmp, "/", name), &st) == -1) {
				xfree(namelist[i]);
				xfree(tmp);
				continue;
			}
		}

		xfree(tmp);

		if (!xstrcmp(name, ".") || !xstrcmp(name, "..")) {
			xfree(namelist[i]);
			continue;
		}

		tmp2 = xstrndup(name, xstrlen(name) - xstrlen(xstrstr(name, ".theme")));

		if (!xstrncmp(text, name, len) || (!xstrncmp(text, tmp2, len) && !themes_only) )
			array_add_check(&completions, tmp2, 1);
		else	xfree(tmp2);

		xfree(namelist[i]);
	}

	xfree(namelist);
}
