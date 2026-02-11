apol_vector_sort_uniquify(apol_vector_t * v, apol_vector_comp_func * cmp, void *data)
{
	if (!v) {
		errno = EINVAL;
		return;
	}
	if (cmp == NULL) {
		cmp = vector_int_comp;
	}
	if (v->size > 1) {
		size_t i, j = 0;
		void **new_array;


		for (i = 1; i < v->size; i++) {
			if (cmp(v->array[i], v->array[j], data) != 0) {

				j++;
				v->array[j] = v->array[i];
			} else {

				if (v->fr != NULL) {
					v->fr(v->array[i]);
				}
			}
		}
		v->size = j + 1;

		apol_vector_sort(v, cmp, data);
		j = 0;
		for (i = 1; i < v->size; i++) {
			if (cmp(v->array[i], v->array[j], data) != 0) {

				j++;
				v->array[j] = v->array[i];
			} else {

				if (v->fr != NULL) {
					v->fr(v->array[i]);
				}
			}
		}

		v->size = j + 1;
		if ((new_array = realloc(v->array, v->size * sizeof(void *))) != NULL) {
			v->array = new_array;
			v->capacity = v->size;
		}
	}
}
