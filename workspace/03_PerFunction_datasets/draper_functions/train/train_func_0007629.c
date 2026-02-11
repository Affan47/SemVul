lt_tag_convert_to_locale(lt_tag_t    *tag,
			 lt_error_t **error)
{
	char *retval = NULL;
	lt_string_t *string = NULL;
	lt_error_t *err = NULL;
	const char *mod = NULL;
	char *canonical_tag = NULL;
	lt_tag_t *ctag;

	lt_return_val_if_fail (tag != NULL, NULL);

	canonical_tag = lt_tag_canonicalize(tag, &err);
	if (!canonical_tag)
		goto bail;
	ctag = lt_tag_new();
	if (!lt_tag_parse(ctag, canonical_tag, &err)) {
		lt_tag_unref(ctag);
		goto bail;
	}
	string = lt_string_new(NULL);
	lt_string_append(string, lt_lang_get_better_tag(ctag->language));
	if (ctag->region)
		lt_string_append_printf(string, "_%s",
					lt_region_get_tag(ctag->region));
	if (ctag->script) {
		mod = lt_script_convert_to_modifier(ctag->script);
		if (mod)
			lt_string_append_printf(string, "@%s", mod);
	}
	lt_tag_unref(ctag);

  bail:
	if (canonical_tag)
		free(canonical_tag);
	if (string)
		retval = lt_string_free(string, FALSE);
	if (lt_error_is_set(err, LT_ERR_ANY)) {
		if (error)
			*error = lt_error_ref(err);
		else
			lt_error_print(err, LT_ERR_ANY);
		lt_error_unref(err);
		if (retval)
			free(retval);
		retval = NULL;
	}

	return retval;
}
