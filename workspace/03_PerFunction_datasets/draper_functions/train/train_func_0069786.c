radeon_test_moves(struct radeon_device *rdev)
{
	if (rdev->asic->copy.dma)
		radeon_do_test_moves(rdev, RADEON_TEST_COPY_DMA);
	if (rdev->asic->copy.blit)
		radeon_do_test_moves(rdev, RADEON_TEST_COPY_BLIT);
}
