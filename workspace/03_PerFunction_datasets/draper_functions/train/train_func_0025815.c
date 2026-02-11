xen_hyper_do_domain(struct xen_hyper_cmd_args *da)
{
	int i;

	if (da->cnt) {
		if (da->cnt == 1) {
			xhdt->last = da->context[0];
		}
		for (i = 0; i < da->cnt; i++) {
			dump_struct("domain", da->addr[i], 0);
		}
	} else {
		dump_struct("domain", xhdt->last->domain, 0);
	}
}
