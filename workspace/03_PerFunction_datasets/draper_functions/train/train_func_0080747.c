radeon_fb_output_poll_changed(struct radeon_device *rdev)
{
	if (rdev->mode_info.rfbdev)
		drm_fb_helper_hotplug_event(&rdev->mode_info.rfbdev->helper);
}
