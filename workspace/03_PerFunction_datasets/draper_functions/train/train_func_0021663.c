aa_label_parse(struct aa_label *base, const char *str,
				gfp_t gfp, bool create, bool force_stack)
{
	DEFINE_VEC(profile, vec);
	struct aa_label *label;
	int i, len, stack = 0, error;
	char *split;

	AA_BUG(!base);
	AA_BUG(!str);

	str = skip_spaces(str);
	len = label_count_str_entries(str);
	if (*str == '&' || force_stack) {

		stack = base->size;
		len += stack;
		if (*str == '&')
			str++;
	}
	error = vec_setup(profile, vec, len, gfp);
	if (error)
		return ERR_PTR(error);

	for (i = 0; i < stack; i++)
		vec[i] = aa_get_profile(base->vec[i]);

	for (split = strstr(str, "//&"), i = stack; split && i < len; i++) {
		vec[i] = aa_fqlookupn_profile(base, str, split - str);
		if (!vec[i])
			goto fail;
		str = split + 3;
		split = strstr(str, "//&");
	}

	if (i < len) {
		vec[i] = aa_fqlookupn_profile(base, str, strlen(str));
		if (!vec[i])
			goto fail;
	}
	if (len == 1)

		return &vec[0]->label;

	len -= aa_vec_unique(vec, len, VEC_FLAG_TERMINATE);

	if (len == 1) {
		label = aa_get_label(&vec[0]->label);
		goto out;
	}

	if (create)
		label = aa_vec_find_or_create_label(vec, len, gfp);
	else
		label = vec_find(vec, len);
	if (!label)
		goto fail;

out:

	vec_cleanup(profile, vec, len);
	return label;

fail:
	label = ERR_PTR(-ENOENT);
	goto out;
}
