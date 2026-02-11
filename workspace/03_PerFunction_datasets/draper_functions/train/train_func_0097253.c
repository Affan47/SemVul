edac_create_debugfs_nodes(struct mem_ctl_info *mci)
{
	struct dentry *d, *parent;
	char name[80];
	int i;

	if (!edac_debugfs)
		return -ENODEV;

	d = debugfs_create_dir(mci->dev.kobj.name, edac_debugfs);
	if (!d)
		return -ENOMEM;
	parent = d;

	for (i = 0; i < mci->n_layers; i++) {
		sprintf(name, "fake_inject_%s",
			     edac_layer_name[mci->layers[i].type]);
		d = debugfs_create_u8(name, S_IRUGO | S_IWUSR, parent,
				      &mci->fake_inject_layer[i]);
		if (!d)
			goto nomem;
	}

	d = debugfs_create_bool("fake_inject_ue", S_IRUGO | S_IWUSR, parent,
				&mci->fake_inject_ue);
	if (!d)
		goto nomem;

	d = debugfs_create_u16("fake_inject_count", S_IRUGO | S_IWUSR, parent,
				&mci->fake_inject_count);
	if (!d)
		goto nomem;

	d = debugfs_create_file("fake_inject", S_IWUSR, parent,
				&mci->dev,
				&debug_fake_inject_fops);
	if (!d)
		goto nomem;

	mci->debugfs = parent;
	return 0;
nomem:
	edac_debugfs_remove_recursive(mci->debugfs);
	return -ENOMEM;
}
