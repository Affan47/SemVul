pvr2_sysfs_add_debugifc(struct pvr2_sysfs *sfp)
{
	struct pvr2_sysfs_debugifc *dip;
	int ret;

	dip = kzalloc(sizeof(*dip),GFP_KERNEL);
	if (!dip) return;
	sysfs_attr_init(&dip->attr_debugcmd.attr);
	dip->attr_debugcmd.attr.name = "debugcmd";
	dip->attr_debugcmd.attr.mode = S_IRUGO|S_IWUSR|S_IWGRP;
	dip->attr_debugcmd.show = debugcmd_show;
	dip->attr_debugcmd.store = debugcmd_store;
	sysfs_attr_init(&dip->attr_debuginfo.attr);
	dip->attr_debuginfo.attr.name = "debuginfo";
	dip->attr_debuginfo.attr.mode = S_IRUGO;
	dip->attr_debuginfo.show = debuginfo_show;
	sfp->debugifc = dip;
	ret = device_create_file(sfp->class_dev,&dip->attr_debugcmd);
	if (ret < 0) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	} else {
		dip->debugcmd_created_ok = !0;
	}
	ret = device_create_file(sfp->class_dev,&dip->attr_debuginfo);
	if (ret < 0) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	} else {
		dip->debuginfo_created_ok = !0;
	}
}
