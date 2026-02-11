pnp_add_resource(struct pnp_dev *dev,
				      struct resource *res)
{
	struct pnp_resource *pnp_res;

	pnp_res = pnp_new_resource(dev);
	if (!pnp_res) {
		dev_err(&dev->dev, "can't add resource %pR\n", res);
		return NULL;
	}

	pnp_res->res = *res;
	pnp_res->res.name = dev->name;
	dev_dbg(&dev->dev, "%pR\n", res);
	return pnp_res;
}
