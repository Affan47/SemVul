dce_v10_0_resume_mc_access(struct amdgpu_device *adev,
				       struct amdgpu_mode_mc_save *save)
{
	u32 tmp, frame_count;
	int i, j;


	for (i = 0; i < adev->mode_info.num_crtc; i++) {
		WREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS_HIGH + crtc_offsets[i],
		       upper_32_bits(adev->mc.vram_start));
		WREG32(mmGRPH_SECONDARY_SURFACE_ADDRESS_HIGH + crtc_offsets[i],
		       upper_32_bits(adev->mc.vram_start));
		WREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS + crtc_offsets[i],
		       (u32)adev->mc.vram_start);
		WREG32(mmGRPH_SECONDARY_SURFACE_ADDRESS + crtc_offsets[i],
		       (u32)adev->mc.vram_start);

		if (save->crtc_enabled[i]) {
			tmp = RREG32(mmMASTER_UPDATE_MODE + crtc_offsets[i]);
			if (REG_GET_FIELD(tmp, MASTER_UPDATE_MODE, MASTER_UPDATE_MODE) != 3) {
				tmp = REG_SET_FIELD(tmp, MASTER_UPDATE_MODE, MASTER_UPDATE_MODE, 3);
				WREG32(mmMASTER_UPDATE_MODE + crtc_offsets[i], tmp);
			}
			tmp = RREG32(mmGRPH_UPDATE + crtc_offsets[i]);
			if (REG_GET_FIELD(tmp, GRPH_UPDATE, GRPH_UPDATE_LOCK)) {
				tmp = REG_SET_FIELD(tmp, GRPH_UPDATE, GRPH_UPDATE_LOCK, 0);
				WREG32(mmGRPH_UPDATE + crtc_offsets[i], tmp);
			}
			tmp = RREG32(mmMASTER_UPDATE_LOCK + crtc_offsets[i]);
			if (REG_GET_FIELD(tmp, MASTER_UPDATE_LOCK, MASTER_UPDATE_LOCK)) {
				tmp = REG_SET_FIELD(tmp, MASTER_UPDATE_LOCK, MASTER_UPDATE_LOCK, 0);
				WREG32(mmMASTER_UPDATE_LOCK + crtc_offsets[i], tmp);
			}
			for (j = 0; j < adev->usec_timeout; j++) {
				tmp = RREG32(mmGRPH_UPDATE + crtc_offsets[i]);
				if (REG_GET_FIELD(tmp, GRPH_UPDATE, GRPH_SURFACE_UPDATE_PENDING) == 0)
					break;
				udelay(1);
			}
			tmp = RREG32(mmCRTC_BLANK_CONTROL + crtc_offsets[i]);
			tmp = REG_SET_FIELD(tmp, CRTC_BLANK_CONTROL, CRTC_BLANK_DATA_EN, 0);
			WREG32(mmCRTC_UPDATE_LOCK + crtc_offsets[i], 1);
			WREG32(mmCRTC_BLANK_CONTROL + crtc_offsets[i], tmp);
			WREG32(mmCRTC_UPDATE_LOCK + crtc_offsets[i], 0);

			frame_count = amdgpu_display_vblank_get_counter(adev, i);
			for (j = 0; j < adev->usec_timeout; j++) {
				if (amdgpu_display_vblank_get_counter(adev, i) != frame_count)
					break;
				udelay(1);
			}
		}
	}

	WREG32(mmVGA_MEMORY_BASE_ADDRESS_HIGH, upper_32_bits(adev->mc.vram_start));
	WREG32(mmVGA_MEMORY_BASE_ADDRESS, lower_32_bits(adev->mc.vram_start));


	WREG32(mmVGA_HDP_CONTROL, save->vga_hdp_control);
	mdelay(1);
	WREG32(mmVGA_RENDER_CONTROL, save->vga_render_control);
}
