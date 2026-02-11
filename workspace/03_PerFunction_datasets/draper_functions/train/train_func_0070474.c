model_sort(const seaudit_log_t * log, seaudit_model_t * model)
{
	size_t i, j, num_messages = apol_vector_get_size(model->messages);
	apol_vector_t *sup = NULL, *unsup = NULL;
	seaudit_message_t *m;
	seaudit_sort_t *s;
	int supported = 0, retval = -1, error = 0;
	if (apol_vector_get_size(model->sorts) == 0) {
		retval = 0;
		goto cleanup;
	}

	if ((sup = apol_vector_create_with_capacity(num_messages, NULL)) == NULL ||
	    (unsup = apol_vector_create_with_capacity(num_messages, NULL)) == NULL) {
		error = errno;
		ERR(log, "%s", strerror(error));
		goto cleanup;
	}
	for (i = 0; i < num_messages; i++) {
		m = apol_vector_get_element(model->messages, i);
		supported = 0;
		for (j = 0; j < apol_vector_get_size(model->sorts); j++) {
			s = apol_vector_get_element(model->sorts, j);
			if ((supported = sort_is_supported(s, m)) != 0) {
				break;
			}
		}
		if ((supported && apol_vector_append(sup, m) < 0) || (!supported && apol_vector_append(unsup, m) < 0)) {
			error = errno;
			ERR(log, "%s", strerror(error));
			goto cleanup;
		}
	}
	apol_vector_sort(sup, message_comp, model);
	if (apol_vector_cat(sup, unsup) < 0) {
		error = errno;
		ERR(log, "%s", strerror(error));
		goto cleanup;
	}
	apol_vector_destroy(&model->messages);
	model->messages = sup;
	sup = NULL;
	retval = 0;
      cleanup:
	apol_vector_destroy(&sup);
	apol_vector_destroy(&unsup);
	if (retval != 0) {
		errno = error;
	}
	return retval;
}
