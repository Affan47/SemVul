git_config_multivar_iterator_new(git_config_iterator **out, const git_config *cfg, const char *name, const char *regexp)
{
	multivar_iter *iter = NULL;
	git_config_iterator *inner = NULL;
	int error;

	if ((error = git_config_iterator_new(&inner, cfg)) < 0)
		return error;

	iter = git__calloc(1, sizeof(multivar_iter));
	GITERR_CHECK_ALLOC(iter);

	if ((error = git_config__normalize_name(name, &iter->name)) < 0)
		goto on_error;

	if (regexp != NULL) {
		error = regcomp(&iter->regex, regexp, REG_EXTENDED);
		if (error < 0) {
			giterr_set_regex(&iter->regex, error);
			error = -1;
			regfree(&iter->regex);
			goto on_error;
		}

		iter->have_regex = 1;
	}

	iter->iter = inner;
	iter->parent.free = multivar_iter_free;
	iter->parent.next = multivar_iter_next;

	*out = (git_config_iterator *) iter;

	return 0;

on_error:

	inner->free(inner);
	git__free(iter);
	return error;
}
