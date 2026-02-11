gnm_strip_missing (gnm_float *data, int *n, GSList *missing)
{
	unsigned src, dst;

	if (missing == NULL)
		return;

	for (src = dst = 0; (int)dst < *n; src++) {
		if (missing && src == GPOINTER_TO_UINT (missing->data)) {
			missing = missing->next;
			(*n)--;
		} else {
			data[dst] = data[src];
			dst++;
		}
	}
}
