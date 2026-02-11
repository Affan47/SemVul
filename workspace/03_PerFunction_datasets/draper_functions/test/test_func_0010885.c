xen_hyper_alloc_domain_context_space(int domains)
{
	if (xhdt->context_array == NULL) {
		if (!(xhdt->context_array =
			malloc(domains * sizeof(struct xen_hyper_domain_context)))) {
			error(FATAL, "cannot malloc context array (%d domains).",
				domains);
		}
		xhdt->context_array_cnt = domains;
	} else if (domains > xhdt->context_array_cnt) {
		struct xen_hyper_domain_context *dc;
		int i;
		for (dc = xhdt->context_array, i = 0;
		     i < xhdt->context_array_cnt; ++dc, ++i) {
			if (dc->vcpu)
				free(dc->vcpu);
		}
		if (!(xhdt->context_array =
			realloc(xhdt->context_array,
				domains * sizeof(struct xen_hyper_domain_context)))) {
			error(FATAL, "cannot realloc context array (%d domains).",
				domains);
		}
		xhdt->context_array_cnt = domains;
	}
	BZERO(xhdt->context_array,
		domains * sizeof(struct xen_hyper_domain_context));
}
