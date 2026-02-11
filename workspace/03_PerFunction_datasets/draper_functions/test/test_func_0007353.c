get_aux(khash_t(lib) *aux, const char *lib)
{
	khint_t k = kh_get(lib, aux, lib);
	if (k == kh_end(aux)) {
		int ret;
		char *p = strdup(lib);
		lib_aux_t *q;
		k = kh_put(lib, aux, p, &ret);
		q = &kh_val(aux, k);
		q->left = kh_init(best);
		q->rght = kh_init(best);
		q->n_checked = q->n_removed = 0;
		return q;
	} else return &kh_val(aux, k);
}
