rv515_mc_stop(struct radeon_device *rdev, struct rv515_mc_save *save)
{
	u32 crtc_enabled, tmp, frame_count, blackout;
	int i, j;

	save->vga_render_control = RREG32(R_000300_VGA_RENDER_CONTROL);
	save->vga_hdp_control = RREG32(R_000328_VGA_HDP_CONTROL);


	WREG32(R_000300_VGA_RENDER_CONTROL, 0);

	for (i = 0; i < rdev->num_crtc; i++) {
		crtc_enabled = RREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i]) & AVIVO_CRTC_EN;
		if (crtc_enabled) {
			save->crtc_enabled[i] = true;
			tmp = RREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i]);
			if (!(tmp & AVIVO_CRTC_DISP_READ_REQUEST_DISABLE)) {
				radeon_wait_for_vblank(rdev, i);
				WREG32(AVIVO_D1CRTC_UPDATE_LOCK + crtc_offsets[i], 1);
				tmp |= AVIVO_CRTC_DISP_READ_REQUEST_DISABLE;
				WREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i], tmp);
				WREG32(AVIVO_D1CRTC_UPDATE_LOCK + crtc_offsets[i], 0);
			}

			frame_count = radeon_get_vblank_counter(rdev, i);
			for (j = 0; j < rdev->usec_timeout; j++) {
				if (radeon_get_vblank_counter(rdev, i) != frame_count)
					break;
				udelay(1);
			}


			WREG32(AVIVO_D1CRTC_UPDATE_LOCK + crtc_offsets[i], 1);
			tmp = RREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i]);
			tmp &= ~AVIVO_CRTC_EN;
			WREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i], tmp);
			WREG32(AVIVO_D1CRTC_UPDATE_LOCK + crtc_offsets[i], 0);
			save->crtc_enabled[i] = false;

		} else {
			save->crtc_enabled[i] = false;
		}
	}

	radeon_mc_wait_for_idle(rdev);

	if (rdev->family >= CHIP_R600) {
		if (rdev->family >= CHIP_RV770)
			blackout = RREG32(R700_MC_CITF_CNTL);
		else
			blackout = RREG32(R600_CITF_CNTL);
		if ((blackout & R600_BLACKOUT_MASK) != R600_BLACKOUT_MASK) {

			WREG32(R600_BIF_FB_EN, 0);

			blackout |= R600_BLACKOUT_MASK;
			if (rdev->family >= CHIP_RV770)
				WREG32(R700_MC_CITF_CNTL, blackout);
			else
				WREG32(R600_CITF_CNTL, blackout);
		}
	}

	udelay(100);


	for (i = 0; i < rdev->num_crtc; i++) {
		if (save->crtc_enabled[i]) {
			tmp = RREG32(AVIVO_D1GRPH_UPDATE + crtc_offsets[i]);
			if (!(tmp & AVIVO_D1GRPH_UPDATE_LOCK)) {
				tmp |= AVIVO_D1GRPH_UPDATE_LOCK;
				WREG32(AVIVO_D1GRPH_UPDATE + crtc_offsets[i], tmp);
			}
			tmp = RREG32(AVIVO_D1MODE_MASTER_UPDATE_LOCK + crtc_offsets[i]);
			if (!(tmp & 1)) {
				tmp |= 1;
				WREG32(AVIVO_D1MODE_MASTER_UPDATE_LOCK + crtc_offsets[i], tmp);
			}
		}
	}
}
