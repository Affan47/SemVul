apol_mls_range_create_from_literal(const char *mls_range_string)
{
	if (mls_range_string == NULL) {
		errno = EINVAL;
		return NULL;
	}

	apol_mls_range_t *r = apol_mls_range_create();
	if (r == NULL) {
		return NULL;
	}
	char *dash;
	if ((dash = strchr(mls_range_string, '-')) == NULL) {

		apol_mls_level_t *l = apol_mls_level_create_from_literal(mls_range_string);
		if (l == NULL) {
			apol_mls_range_destroy(&r);
			return NULL;
		}
		r->low = l;
	} else {

		if (dash == mls_range_string) {
			apol_mls_range_destroy(&r);
			errno = EINVAL;
			return NULL;
		}
		char *s = strndup(mls_range_string, dash - mls_range_string);
		if (s == NULL) {
			apol_mls_range_destroy(&r);
			return NULL;
		}
		apol_mls_level_t *l = apol_mls_level_create_from_literal(s);
		if (l == NULL) {
			apol_mls_range_destroy(&r);
			free(s);
			return NULL;
		}
		r->low = l;
		free(s);
		l = NULL;

		if ((l = apol_mls_level_create_from_literal(dash + 1)) == NULL) {
			apol_mls_range_destroy(&r);
			return NULL;
		}
		r->high = l;
	}
	return r;
}
