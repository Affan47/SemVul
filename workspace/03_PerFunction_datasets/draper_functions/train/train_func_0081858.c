r100_asic_reset(struct radeon_device *rdev)
{
	struct r100_mc_save save;
	u32 status, tmp;
	int ret = 0;

	status = RREG32(R_000E40_RBBM_STATUS);
	if (!G_000E40_GUI_ACTIVE(status)) {
		return 0;
	}
	r100_mc_stop(rdev, &save);
	status = RREG32(R_000E40_RBBM_STATUS);
	dev_info(rdev->dev, "(%s:%d) RBBM_STATUS=0x%08X\n", __func__, __LINE__, status);

	WREG32(RADEON_CP_CSQ_CNTL, 0);
	tmp = RREG32(RADEON_CP_RB_CNTL);
	WREG32(RADEON_CP_RB_CNTL, tmp | RADEON_RB_RPTR_WR_ENA);
	WREG32(RADEON_CP_RB_RPTR_WR, 0);
	WREG32(RADEON_CP_RB_WPTR, 0);
	WREG32(RADEON_CP_RB_CNTL, tmp);

	pci_save_state(rdev->pdev);

	r100_bm_disable(rdev);
	WREG32(R_0000F0_RBBM_SOFT_RESET, S_0000F0_SOFT_RESET_SE(1) |
					S_0000F0_SOFT_RESET_RE(1) |
					S_0000F0_SOFT_RESET_PP(1) |
					S_0000F0_SOFT_RESET_RB(1));
	RREG32(R_0000F0_RBBM_SOFT_RESET);
	mdelay(500);
	WREG32(R_0000F0_RBBM_SOFT_RESET, 0);
	mdelay(1);
	status = RREG32(R_000E40_RBBM_STATUS);
	dev_info(rdev->dev, "(%s:%d) RBBM_STATUS=0x%08X\n", __func__, __LINE__, status);

	WREG32(R_0000F0_RBBM_SOFT_RESET, S_0000F0_SOFT_RESET_CP(1));
	RREG32(R_0000F0_RBBM_SOFT_RESET);
	mdelay(500);
	WREG32(R_0000F0_RBBM_SOFT_RESET, 0);
	mdelay(1);
	status = RREG32(R_000E40_RBBM_STATUS);
	dev_info(rdev->dev, "(%s:%d) RBBM_STATUS=0x%08X\n", __func__, __LINE__, status);

	pci_restore_state(rdev->pdev);
	r100_enable_bm(rdev);

	if (G_000E40_SE_BUSY(status) || G_000E40_RE_BUSY(status) ||
		G_000E40_TAM_BUSY(status) || G_000E40_PB_BUSY(status)) {
		dev_err(rdev->dev, "failed to reset GPU\n");
		ret = -1;
	} else
		dev_info(rdev->dev, "GPU reset succeed\n");
	r100_mc_resume(rdev, &save);
	return ret;
}
