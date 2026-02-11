prop_get_string(prop_set_t *ps, property_t prop, char *t, size_t size)
{
	char *target;
	char *s;

	g_assert(ps != NULL);
	g_assert(NULL == t || size > 0);

	if (!prop_in_range(ps, prop))
		g_error("prop_get_gchar: unknown property %d", prop);
	if (PROP(ps,prop).type != PROP_TYPE_STRING)
		g_error("Type mismatch getting value for [%s] of type"
			" %s when %s was expected",
			PROP(ps,prop).name,
			prop_type_str[PROP(ps,prop).type].name,
			prop_type_str[PROP_TYPE_STRING].name);

	s = *PROP(ps,prop).data.string.value;

	target = t;
	if (target == NULL) {


		target = g_strdup(s);
	} else {


		if (s == NULL) {
			target[0] = '\0';
			target = NULL;
		} else {
			clamp_strcpy(target, size, s);
		}
	}

	return target;
}
