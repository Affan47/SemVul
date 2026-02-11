pnp_clean_resource_table(struct pnp_dev *dev)
{
	struct pnp_resource *pnp_res, *tmp;

	list_for_each_entry_safe(pnp_res, tmp, &dev->resources, list) {
		if (pnp_res->res.flags & IORESOURCE_AUTO)
			pnp_free_resource(pnp_res);
	}
}
