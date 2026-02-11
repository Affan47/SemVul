apol_infoflow_direct_define(const apol_policy_t * p,
				       const apol_infoflow_edge_t * edge, unsigned int direction, apol_infoflow_result_t * result)
{
	apol_infoflow_step_t *step = NULL;
	if (apol_vector_get_size(result->steps) == 0) {
		if ((step = calloc(1, sizeof(*step))) == NULL ||
		    (step->rules = apol_vector_create(NULL)) == NULL || apol_vector_append(result->steps, step) < 0) {
			apol_infoflow_step_free(step);
			ERR(p, "%s", strerror(ENOMEM));
			return -1;
		}
		step->start_type = result->start_type;
		step->end_type = result->end_type;
		step->weight = 0;
	} else {
		step = (apol_infoflow_step_t *) apol_vector_get_element(result->steps, 0);
	}
	if (apol_vector_cat(step->rules, edge->rules) < 0) {
		ERR(p, "%s", strerror(ENOMEM));
		return -1;
	}
	result->direction |= direction;

	if (edge->length < (int)result->length) {
		result->length = edge->length;
	}
	return 0;
}
