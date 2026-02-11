sony_nc_fanspeed_cleanup(struct platform_device *pd)
{
	if (fan_handle) {
		device_remove_file(&pd->dev, fan_handle);
		kfree(fan_handle);
		fan_handle = NULL;
	}
	if (hsf_handle) {
		device_remove_file(&pd->dev, hsf_handle);
		kfree(hsf_handle);
		hsf_handle = NULL;
	}
}
