pinctrl_get(struct device *dev)
{
	struct pinctrl *p;

	if (WARN_ON(!dev))
		return ERR_PTR(-EINVAL);


	p = find_pinctrl(dev);
	if (p != NULL) {
		dev_dbg(dev, "obtain a copy of previously claimed pinctrl\n");
		kref_get(&p->users);
		return p;
	}

	return create_pinctrl(dev);
}
