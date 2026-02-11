__of_phy_provider_register(struct device *dev,
	struct module *owner, struct phy * (*of_xlate)(struct device *dev,
	struct of_phandle_args *args))
{
	struct phy_provider *phy_provider;

	phy_provider = kzalloc(sizeof(*phy_provider), GFP_KERNEL);
	if (!phy_provider)
		return ERR_PTR(-ENOMEM);

	phy_provider->dev = dev;
	phy_provider->owner = owner;
	phy_provider->of_xlate = of_xlate;

	mutex_lock(&phy_provider_mutex);
	list_add_tail(&phy_provider->list, &phy_provider_list);
	mutex_unlock(&phy_provider_mutex);

	return phy_provider;
}
