ib_port_release(struct kobject *kobj)
{
	struct ib_port *p = container_of(kobj, struct ib_port, kobj);
	struct attribute *a;
	int i;

	if (p->gid_group.attrs) {
		for (i = 0; (a = p->gid_group.attrs[i]); ++i)
			kfree(a);

		kfree(p->gid_group.attrs);
	}

	if (p->pkey_group.attrs) {
		for (i = 0; (a = p->pkey_group.attrs[i]); ++i)
			kfree(a);

		kfree(p->pkey_group.attrs);
	}

	kfree(p);
}
