mx27_camera_emma_prp_reset(struct mx2_camera_dev *pcdev)
{
	int count = 0;

	readl(pcdev->base_emma + PRP_CNTL);
	writel(PRP_CNTL_SWRST, pcdev->base_emma + PRP_CNTL);
	while (count++ < 100) {
		if (!(readl(pcdev->base_emma + PRP_CNTL) & PRP_CNTL_SWRST))
			return 0;
		barrier();
		udelay(1);
	}

	return -ETIMEDOUT;
}
