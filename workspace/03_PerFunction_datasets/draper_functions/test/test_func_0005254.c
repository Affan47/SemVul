_parse_next_key(s_p_hashtbl_t *hashtbl,
			   const char *line, char **leftover, bool ignore_new)
{
	char *key, *value;
	s_p_values_t *p;
	char *new_leftover;

	_keyvalue_regex_init();

	if (_keyvalue_regex(line, &key, &value, &new_leftover) == 0) {
		if ((p = _conf_hashtbl_lookup(hashtbl, key))) {
			_handle_keyvalue_match(p, value,
					       new_leftover, &new_leftover);
			*leftover = new_leftover;
		} else if (ignore_new) {
			debug("Parsing error at unrecognized key: %s", key);
			*leftover = (char *)line;
		} else {
			error("Parsing error at unrecognized key: %s", key);
			xfree(key);
			xfree(value);
			*leftover = (char *)line;
			return 0;
		}
		xfree(key);
		xfree(value);
	} else {
		*leftover = (char *)line;
	}

	return 1;
}
