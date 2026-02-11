git_diff_driver_registry_free(git_diff_driver_registry *reg)
{
	git_diff_driver *drv;

	if (!reg)
		return;

	git_strmap_foreach_value(reg->drivers, drv, git_diff_driver_free(drv));
	git_strmap_free(reg->drivers);
	git__free(reg);
}
