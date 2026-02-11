i915_teardown_sysfs(struct drm_device *dev)
{
	sysfs_remove_bin_file(&dev->primary->kdev->kobj, &error_state_attr);
	if (IS_VALLEYVIEW(dev) || IS_CHERRYVIEW(dev))
		sysfs_remove_files(&dev->primary->kdev->kobj, vlv_attrs);
	else
		sysfs_remove_files(&dev->primary->kdev->kobj, gen6_attrs);
	device_remove_bin_file(dev->primary->kdev,  &dpf_attrs_1);
	device_remove_bin_file(dev->primary->kdev,  &dpf_attrs);
#ifdef CONFIG_PM
	sysfs_unmerge_group(&dev->primary->kdev->kobj, &rc6_attr_group);
	sysfs_unmerge_group(&dev->primary->kdev->kobj, &rc6p_attr_group);
#endif
}
