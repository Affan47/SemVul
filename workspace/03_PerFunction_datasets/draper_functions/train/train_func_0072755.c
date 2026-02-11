mx27_update_emma_buf(struct mx2_camera_dev *pcdev,
				 unsigned long phys, int bufnum)
{
	struct mx2_fmt_cfg *prp = pcdev->emma_prp;

	if (prp->cfg.channel == 1) {
		writel(phys, pcdev->base_emma +
				PRP_DEST_RGB1_PTR + 4 * bufnum);
	} else {
		writel(phys, pcdev->base_emma +
			PRP_DEST_Y_PTR - 0x14 * bufnum);
		if (prp->out_fmt == V4L2_PIX_FMT_YUV420) {
			u32 imgsize = pcdev->soc_host.icd->user_height *
					pcdev->soc_host.icd->user_width;

			writel(phys + imgsize, pcdev->base_emma +
				PRP_DEST_CB_PTR - 0x14 * bufnum);
			writel(phys + ((5 * imgsize) / 4), pcdev->base_emma +
				PRP_DEST_CR_PTR - 0x14 * bufnum);
		}
	}
}
