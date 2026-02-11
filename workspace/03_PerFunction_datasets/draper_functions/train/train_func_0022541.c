camif_hw_set_target_format(struct camif_vp *vp)
{
	struct camif_dev *camif = vp->camif;
	struct camif_frame *frame = &vp->out_frame;
	u32 cfg;

	pr_debug("fw: %d, fh: %d color: %d\n", frame->f_width,
		 frame->f_height, vp->out_fmt->color);

	cfg = camif_read(camif, S3C_CAMIF_REG_CITRGFMT(vp->id, vp->offset));
	cfg &= ~CITRGFMT_TARGETSIZE_MASK;

	if (camif->variant->ip_revision == S3C244X_CAMIF_IP_REV) {

		cfg |= CITRGFMT_IN422;
		cfg &= ~CITRGFMT_OUT422;
		if (vp->out_fmt->color == IMG_FMT_YCBCR422P)
			cfg |= CITRGFMT_OUT422;
	} else {
		cfg &= ~CITRGFMT_OUTFORMAT_MASK;
		switch (vp->out_fmt->color) {
		case IMG_FMT_RGB565...IMG_FMT_XRGB8888:
			cfg |= CITRGFMT_OUTFORMAT_RGB;
			break;
		case IMG_FMT_YCBCR420...IMG_FMT_YCRCB420:
			cfg |= CITRGFMT_OUTFORMAT_YCBCR420;
			break;
		case IMG_FMT_YCBCR422P:
			cfg |= CITRGFMT_OUTFORMAT_YCBCR422;
			break;
		case IMG_FMT_YCBYCR422...IMG_FMT_CRYCBY422:
			cfg |= CITRGFMT_OUTFORMAT_YCBCR422I;
			break;
		}
	}


	if (vp->rotation == 90 || vp->rotation == 270)
		cfg |= (frame->f_height << 16) | frame->f_width;
	else
		cfg |= (frame->f_width << 16) | frame->f_height;
	camif_write(camif, S3C_CAMIF_REG_CITRGFMT(vp->id, vp->offset), cfg);


	cfg = camif_read(camif, S3C_CAMIF_REG_CITAREA(vp->id, vp->offset));
	cfg &= ~CITAREA_MASK;
	cfg |= (frame->f_width * frame->f_height);
	camif_write(camif, S3C_CAMIF_REG_CITAREA(vp->id, vp->offset), cfg);
}
