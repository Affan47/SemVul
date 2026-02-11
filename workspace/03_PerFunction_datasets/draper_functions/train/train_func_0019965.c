_lt_ext_ldml_u_parse_tag(lt_ext_module_data_t  *data,
			 const char            *subtag,
			 lt_error_t           **error)
{
	lt_ext_ldml_u_data_t *d = (lt_ext_ldml_u_data_t *)data;
	lt_bool_t retval = TRUE;
	size_t len = strlen(subtag);

  restate:
	switch (d->state) {
	    case STATE_NONE:
		    if (len >= 3 && len <= 8) {
			    d->state = STATE_ATTRIBUTE;
		    } else if (len == 2) {
			    d->state = STATE_KEY;
		    } else {
			    lt_error_set(error, LT_ERR_FAIL_ON_SCANNER,
					 "Invalid syntax: expected to see an attribute or a key, but `%s'", subtag);
			    break;
		    }
		    goto restate;
	    case STATE_ATTRIBUTE:
		    if (len >= 3 && len <= 8) {
			    d->attributes = lt_list_append(d->attributes,
							   strdup(subtag),
							   free);

		    } else {

			    d->state = STATE_KEY;
			    goto restate;
		    }
		    break;
	    case STATE_KEY:
		    if (len != 2) {
			    lt_error_set(error, LT_ERR_FAIL_ON_SCANNER,
					 "Invalid syntax: expected to see a key, but `%s'", subtag);
			    break;
		    }
		    _lt_ext_ldml_u_lookup_key(d, subtag, error);
		    d->tags = lt_list_append(d->tags,
					     lt_string_new(subtag),
					     (lt_destroy_func_t)lt_string_unref);
		    break;
	    case STATE_TYPE:
		    if (len >= 3 && len <= 8) {
			    lt_list_t *l;
			    lt_string_t *s;

			    if (!_lt_ext_ldml_u_lookup_type(d, subtag, error)) {
				    if (!lt_error_is_set(*error, LT_ERR_ANY))
					    lt_error_set(error, LT_ERR_FAIL_ON_SCANNER,
							 "Unknown -u- extension type: %s", subtag);
				    break;
			    }
			    l = lt_list_last(d->tags);
			    if (l == NULL) {
				    lt_error_set(error, LT_ERR_FAIL_ON_SCANNER,
						 "Invalid internal state. failed to find a key container.");
				    break;
			    }
			    s = lt_list_value(l);
			    lt_string_append_printf(s, "-%s", subtag);
		    } else if (len == 2) {
			    d->state = STATE_KEY;
			    goto restate;
		    } else {
			    lt_error_set(error, LT_ERR_FAIL_ON_SCANNER,
					 "Invalid syntax: expected to see a type or a key, but `%s'", subtag);
			    break;
		    }
		    break;
	    default:
		    lt_warn_if_reached();
		    break;
	}

	if (lt_error_is_set(*error, LT_ERR_ANY))
		retval = FALSE;

	return retval;
}
