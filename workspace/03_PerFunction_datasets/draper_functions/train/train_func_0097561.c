trinity_dpm_enable_bapm(struct radeon_device *rdev, bool enable)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);

	if (pi->enable_bapm) {
		trinity_acquire_mutex(rdev);
		trinity_dpm_bapm_enable(rdev, enable);
		trinity_release_mutex(rdev);
	}
}
