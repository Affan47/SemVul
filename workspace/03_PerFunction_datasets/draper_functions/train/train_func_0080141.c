r100_irq_process(struct radeon_device *rdev)
{
	uint32_t status, msi_rearm;
	bool queue_hotplug = false;

	status = r100_irq_ack(rdev);
	if (!status) {
		return IRQ_NONE;
	}
	if (rdev->shutdown) {
		return IRQ_NONE;
	}
	while (status) {

		if (status & RADEON_SW_INT_TEST) {
			radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
		}

		if (status & RADEON_CRTC_VBLANK_STAT) {
			if (rdev->irq.crtc_vblank_int[0]) {
				drm_handle_vblank(rdev->ddev, 0);
				rdev->pm.vblank_sync = true;
				wake_up(&rdev->irq.vblank_queue);
			}
			if (atomic_read(&rdev->irq.pflip[0]))
				radeon_crtc_handle_vblank(rdev, 0);
		}
		if (status & RADEON_CRTC2_VBLANK_STAT) {
			if (rdev->irq.crtc_vblank_int[1]) {
				drm_handle_vblank(rdev->ddev, 1);
				rdev->pm.vblank_sync = true;
				wake_up(&rdev->irq.vblank_queue);
			}
			if (atomic_read(&rdev->irq.pflip[1]))
				radeon_crtc_handle_vblank(rdev, 1);
		}
		if (status & RADEON_FP_DETECT_STAT) {
			queue_hotplug = true;
			DRM_DEBUG("HPD1\n");
		}
		if (status & RADEON_FP2_DETECT_STAT) {
			queue_hotplug = true;
			DRM_DEBUG("HPD2\n");
		}
		status = r100_irq_ack(rdev);
	}
	if (queue_hotplug)
		schedule_delayed_work(&rdev->hotplug_work, 0);
	if (rdev->msi_enabled) {
		switch (rdev->family) {
		case CHIP_RS400:
		case CHIP_RS480:
			msi_rearm = RREG32(RADEON_AIC_CNTL) & ~RS400_MSI_REARM;
			WREG32(RADEON_AIC_CNTL, msi_rearm);
			WREG32(RADEON_AIC_CNTL, msi_rearm | RS400_MSI_REARM);
			break;
		default:
			WREG32(RADEON_MSI_REARM_EN, RV370_MSI_REARM_EN);
			break;
		}
	}
	return IRQ_HANDLED;
}
