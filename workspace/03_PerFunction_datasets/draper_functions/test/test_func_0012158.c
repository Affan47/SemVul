ast_var_indications(struct variable *vp, oid *name, size_t *length,
								  int exact, size_t *var_len, WriteMethod **write_method)
{
	static unsigned long long_ret;
	static char ret_buf[128];
	struct ast_tone_zone *tz = NULL;

	if (header_generic(vp, name, length, exact, var_len, write_method))
		return NULL;

	switch (vp->magic) {
	case ASTINDCOUNT:
	{
		struct ao2_iterator i;

		long_ret = 0;

		i = ast_tone_zone_iterator_init();
		while ((tz = ao2_iterator_next(&i))) {
			tz = ast_tone_zone_unref(tz);
			long_ret++;
		}
		ao2_iterator_destroy(&i);

		return (u_char *) &long_ret;
	}
	case ASTINDCURRENT:
		tz = ast_get_indication_zone(NULL);
		if (tz) {
			ast_copy_string(ret_buf, tz->country, sizeof(ret_buf));
			*var_len = strlen(ret_buf);
			tz = ast_tone_zone_unref(tz);
			return (u_char *) ret_buf;
		}
		*var_len = 0;
		return NULL;
	default:
		break;
	}
	return NULL;
}
