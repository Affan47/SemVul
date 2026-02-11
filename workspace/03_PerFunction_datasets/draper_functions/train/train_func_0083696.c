fdisk_probe_labels(struct fdisk_context *cxt)
{
	size_t i;

	cxt->label = NULL;

	for (i = 0; i < cxt->nlabels; i++) {
		struct fdisk_label *lb = cxt->labels[i];
		struct fdisk_label *org = fdisk_get_label(cxt, NULL);
		int rc;

		if (!lb->op->probe)
			continue;
		if (lb->disabled) {
			DBG(CXT, ul_debugobj(cxt, "%s: disabled -- ignore", lb->name));
			continue;
		}
		DBG(CXT, ul_debugobj(cxt, "probing for %s", lb->name));

		cxt->label = lb;
		rc = lb->op->probe(cxt);
		cxt->label = org;

		if (rc != 1) {
			if (lb->op->deinit)
				lb->op->deinit(lb);
			continue;
		}

		__fdisk_switch_label(cxt, lb);
		return 0;
	}

	DBG(CXT, ul_debugobj(cxt, "no label found"));
	return 1;
}
