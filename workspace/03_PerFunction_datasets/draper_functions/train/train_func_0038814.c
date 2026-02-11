create_most_dci_obj(struct kobject *parent)
{
	struct most_dci_obj *most_dci;
	int retval;

	most_dci = kzalloc(sizeof(*most_dci), GFP_KERNEL);
	if (!most_dci)
		return NULL;

	retval = kobject_init_and_add(&most_dci->kobj, &most_dci_ktype, parent,
				      "dci");
	if (retval) {
		kobject_put(&most_dci->kobj);
		return NULL;
	}
	return most_dci;
}
