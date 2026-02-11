fontFetch (char **error, void *key)
{
	font_t *a;
	fontkey_t *b = (fontkey_t *) key;
	char *suffix;
	FT_Error err;
	const unsigned int b_font_list_len = strlen(b->fontlist);

	*error = NULL;

	a = (font_t *) gdMalloc (sizeof (font_t));
	if (!a) {
		return NULL;
	}

	a->fontlist = (char *) gdMalloc(b_font_list_len + 1);
	if (a->fontlist == NULL) {
		gdFree(a);
		return "could not alloc full list of fonts";
	}
	strncpy(a->fontlist, b->fontlist, b_font_list_len);
	a->fontlist[b_font_list_len] = 0;

	a->flags = b->flags;
	a->library = b->library;
	a->fontpath = NULL;

#ifdef HAVE_LIBFONTCONFIG
	if (!useFontConfig(b->flags))
		*error = font_path(&(a->fontpath), a->fontlist);
	else
		*error = font_pattern(&(a->fontpath), a->fontlist);
#else
	*error = font_path(&(a->fontpath), a->fontlist);
#endif
	if (*error || !a->fontpath || !a->fontpath[0]) {
		gdFree(a->fontlist);
		if (a->fontpath)
			free(a->fontpath);
		gdFree(a);

		if (!*error)
			*error = "font_path() returned an empty font pathname";

		return NULL;
	}

	err = FT_New_Face(*b->library, a->fontpath, 0, &a->face);


	if (!err
	        && ((suffix = strstr(a->fontpath, ".pfa"))
	            || (suffix = strstr(a->fontpath, ".pfb")))
	        && ((strcpy(suffix, ".afm") && (access(a->fontpath, R_OK) == 0))
	            || (strcpy(suffix, ".pfm") && (access(a->fontpath, R_OK) == 0)))) {
		err = FT_Attach_File(a->face, a->fontpath);
	}

	if (err) {
		gdFree (a->fontlist);
		free(a->fontpath);
		gdFree(a);
		*error = "Could not read font";
		return NULL;
	}

	return (void *) a;
}
