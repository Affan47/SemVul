vector_foreach(const vector_t *v, GFunc func, void *data)
{
	size_t i;

	for (i = 0; i < v->n; i++) {
		void *item = &v->base[i * v->element_size];
		(*func)(item, data);
	}
}
