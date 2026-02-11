array_pop(struct array *a)
{
	struct array_item *ai;
	void *retval = NULL;

	__lock(a);
	for (ai = a->a_arr; ai < a->a_arr + a->a_size; ai++) {
		if (ai->ai_data) {
			retval = ai->ai_data;
			ai->ai_data = NULL;
			a->a_items--;
			break;
		}
	}
	__unlock(a);
	return retval;
}
