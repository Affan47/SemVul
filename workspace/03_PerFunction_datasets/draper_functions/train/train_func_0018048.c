identify_token(const char *arg, setter_value *value) {
	char *end;
	if (*arg == '\0')
		return TOKEN_ERROR_EMPTY;

	if (strcmp(arg, "..") == 0) {
		return TOKEN_DOTDOT;
	}

	if (ends_with_x(arg)) {
		const long int i = strtol(arg, &end, 10);
		if ((*end == 'x') && (end - arg == (int)strlen(arg) - 1)) {
			if (i < 0) {
				return TOKEN_ERROR_BAD_COUNT;
			}
			value->uint_data = i;
			return TOKEN_MULTIPLIER;
		}
	} else {
		const float f = strtod(arg, &end);
		if (end - arg == (int)strlen(arg)) {
			if (is_nan_or_inf(f)) {
				return TOKEN_ERROR_BAD_FLOAT;
			}
			value->float_data =f;
			return TOKEN_FLOAT;
		}
	}

	return TOKEN_ERROR_PARSE;
}
