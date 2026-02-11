seaudit_model_remove_filter(seaudit_model_t * model, seaudit_filter_t * filter)
{
	size_t i;
	if (model == NULL || filter == NULL) {
		errno = EINVAL;
		return -1;
	}
	if (apol_vector_get_index(model->filters, filter, NULL, NULL, &i) < 0) {
		errno = EINVAL;
		return -1;
	}
	seaudit_filter_destroy(&filter);
	apol_vector_remove(model->filters, i);
	model->dirty = 1;
	return 0;
}
