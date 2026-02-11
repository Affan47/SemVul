devcgroup_css_alloc(struct cgroup_subsys_state *parent_css)
{
	struct dev_cgroup *dev_cgroup;

	dev_cgroup = kzalloc(sizeof(*dev_cgroup), GFP_KERNEL);
	if (!dev_cgroup)
		return ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&dev_cgroup->exceptions);
	dev_cgroup->behavior = DEVCG_DEFAULT_NONE;

	return &dev_cgroup->css;
}
