pcs_add_pingroup(struct pcs_device *pcs,
					struct device_node *np,
					const char *name,
					int *gpins,
					int ngpins)
{
	struct pcs_pingroup *pingroup;

	pingroup = devm_kzalloc(pcs->dev, sizeof(*pingroup), GFP_KERNEL);
	if (!pingroup)
		return -ENOMEM;

	pingroup->name = name;
	pingroup->np = np;
	pingroup->gpins = gpins;
	pingroup->ngpins = ngpins;

	mutex_lock(&pcs->mutex);
	list_add_tail(&pingroup->node, &pcs->pingroups);
	radix_tree_insert(&pcs->pgtree, pcs->ngroups, pingroup);
	pcs->ngroups++;
	mutex_unlock(&pcs->mutex);

	return 0;
}
