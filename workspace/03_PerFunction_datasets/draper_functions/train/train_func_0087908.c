lt_tag_parse_wildcard(lt_tag_t    *tag,
		      const char  *tag_string,
		      lt_error_t **error)
{
	lt_error_t *err = NULL;
	lt_bool_t ret;

	lt_tag_parser_init(tag);
	ret = _lt_tag_parse(tag, tag_string, TRUE, &err);

	if (!ret && !err) {
		lt_error_set(&err, LT_ERR_FAIL_ON_SCANNER,
			     "Unknown error during parsing a tag.");
	}
	if (lt_error_is_set(err, LT_ERR_ANY)) {
		if (error)
			*error = lt_error_ref(err);
		else
			lt_error_print(err, LT_ERR_ANY);
		lt_error_unref(err);
	}

	return tag->state;
}
