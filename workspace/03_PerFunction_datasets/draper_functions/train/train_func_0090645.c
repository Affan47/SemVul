xen_hyper_refresh_vcpu_context_space(void)
{
	struct xen_hyper_domain_context *dc;
	struct xen_hyper_vcpu_context_array *vcca;
	struct xen_hyper_vcpu_context *vcc;
	int i, j;

	if ((xhvct->flags & XEN_HYPER_VCPU_F_INIT) && !ACTIVE()) {
		return;
	}

	xen_hyper_alloc_vcpu_context_arrays_space(XEN_HYPER_NR_DOMAINS());
	for (i = 0, xht->vcpus = 0, dc = xhdt->context_array,
	vcca = xhvct->vcpu_context_arrays;
	i < XEN_HYPER_NR_DOMAINS(); i++, dc++, vcca++) {
		dc->vcpu_context_array = vcca;
		xen_hyper_alloc_vcpu_context_space(vcca,
			XEN_HYPER_NR_VCPUS_IN_DOM(dc));
		for (j = 0, vcc = vcca->context_array;
		j < XEN_HYPER_NR_VCPUS_IN_DOM(dc); j++, vcc++) {
			xen_hyper_read_vcpu(dc->vcpu[j]);
			xen_hyper_store_vcpu_context(vcc, dc->vcpu[j],
				xhvct->vcpu_struct);
		}
		if (dc == xhdt->idle_domain) {
			xhvct->idle_vcpu_context_array = vcca;
		}
		xht->vcpus += vcca->context_array_cnt;
	}
}
