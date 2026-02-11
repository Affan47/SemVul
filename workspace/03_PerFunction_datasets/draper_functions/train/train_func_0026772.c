evergreen_get_vblank_counter(struct radeon_device *rdev, int crtc)
{
	if (crtc >= rdev->num_crtc)
		return 0;
	else
		return RREG32(CRTC_STATUS_FRAME_COUNT + crtc_offsets[crtc]);
}
