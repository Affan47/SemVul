edac_create_csrow_object(struct mem_ctl_info *mci,
				    struct csrow_info *csrow, int index)
{
	csrow->dev.type = &csrow_attr_type;
	csrow->dev.bus = mci->bus;
	csrow->dev.groups = csrow_dev_groups;
	device_initialize(&csrow->dev);
	csrow->dev.parent = &mci->dev;
	csrow->mci = mci;
	dev_set_name(&csrow->dev, "csrow%d", index);
	dev_set_drvdata(&csrow->dev, csrow);

	edac_dbg(0, "creating (virtual) csrow node %s\n",
		 dev_name(&csrow->dev));

	return device_add(&csrow->dev);
}
