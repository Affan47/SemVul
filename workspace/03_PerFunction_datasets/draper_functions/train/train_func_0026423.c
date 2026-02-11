model_refresh(const seaudit_log_t * log, seaudit_model_t * model)
{
	size_t i, j;
	seaudit_log_t *l;
	const apol_vector_t *v;
	seaudit_message_t *message;
	void *result;
	int error, filter_match;

	if (!model->dirty) {
		return 0;
	}
	apol_vector_destroy(&model->messages);
	apol_vector_destroy(&model->malformed_messages);
	if ((model->messages = apol_vector_create(NULL)) == NULL || (model->malformed_messages = apol_vector_create(NULL)) == NULL) {
		error = errno;
		ERR(log, "%s", strerror(error));
		errno = error;
		return -1;
	}
	for (i = 0; i < apol_vector_get_size(model->logs); i++) {
		l = apol_vector_get_element(model->logs, i);
		v = log_get_messages(l);
		for (j = 0; j < apol_vector_get_size(v); j++) {
			message = apol_vector_get_element(v, j);
			if (apol_bst_get_element(model->hidden_messages, message, NULL, &result) == 0) {
				continue;
			}
			filter_match = model_filter_message(model, message);
			if (((filter_match && model->visible == SEAUDIT_FILTER_VISIBLE_SHOW) ||
			     (!filter_match && model->visible == SEAUDIT_FILTER_VISIBLE_HIDE)) &&
			    apol_vector_append(model->messages, message) < 0) {
				error = errno;
				ERR(log, "%s", strerror(error));
				errno = error;
				return -1;
			}
		}
		v = log_get_malformed_messages(l);
		if (apol_vector_cat(model->malformed_messages, v) < 0) {
			error = errno;
			ERR(log, "%s", strerror(error));
			errno = error;
			return -1;
		}
	}
	if (model_sort(log, model) < 0) {
		return -1;
	}
	model_recalc_stats(model);
	model->dirty = 0;
	return 0;
}
