xen_hyper_id_to_domain_context(domid_t id)
{
	struct xen_hyper_domain_context *dc;
	int i;

	if (xhdt->context_array == NULL ||
		xhdt->context_array->domain == 0) {
		return NULL;
	}
	if (id == XEN_HYPER_DOMAIN_ID_INVALID) {
		return NULL;
	}
	for (i = 0, dc = xhdt->context_array; i < XEN_HYPER_NR_DOMAINS();
		i++, dc++) {
		if (id == dc->domain_id) {
			return dc;
		}
	}
	return NULL;
}
