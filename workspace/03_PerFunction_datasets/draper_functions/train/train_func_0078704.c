apol_mls_level_create_from_qpol_mls_level(const apol_policy_t * p, const qpol_mls_level_t * qpol_level)
{
	apol_mls_level_t *lvl = NULL;
	qpol_iterator_t *iter = NULL;
	const qpol_cat_t *tmp_cat = NULL;
	const char *tmp = NULL;
	int error = 0;

	if (!p || !qpol_level) {
		ERR(p, "%s", strerror(EINVAL));
		errno = EINVAL;
		goto err;
	}

	if ((lvl = apol_mls_level_create()) == NULL) {
		error = errno;
		ERR(p, "%s", strerror(error));
		goto err;
	}
	if (qpol_mls_level_get_sens_name(p->p, qpol_level, &tmp) || qpol_mls_level_get_cat_iter(p->p, qpol_level, &iter)) {
		error = errno;
		goto err;
	}
	if (apol_mls_level_set_sens(p, lvl, tmp) < 0) {
		error = errno;
		ERR(p, "%s", strerror(error));
		goto err;
	}
	for (; !qpol_iterator_end(iter); qpol_iterator_next(iter)) {
		if (qpol_iterator_get_item(iter, (void **)&tmp_cat) < 0 || qpol_cat_get_name(p->p, tmp_cat, &tmp) < 0) {
			error = errno;
			goto err;
		}
		if (apol_mls_level_append_cats(p, lvl, tmp) < 0) {
			error = errno;
			ERR(p, "%s", strerror(error));
			goto err;
		}
	}

	qpol_iterator_destroy(&iter);
	return lvl;

      err:
	apol_mls_level_destroy(&lvl);
	qpol_iterator_destroy(&iter);
	errno = error;
	return NULL;
}
