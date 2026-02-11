s5p_mfc_set_enc_params_vp8(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	struct s5p_mfc_enc_params *p = &ctx->enc_params;
	struct s5p_mfc_vp8_enc_params *p_vp8 = &p->codec.vp8;
	unsigned int reg = 0;
	unsigned int val = 0;

	mfc_debug_enter();

	s5p_mfc_set_enc_params(ctx);


	reg = readl(mfc_regs->e_gop_config);
	reg &= ~(0x3 << 16);
	reg |= ((p->num_b_frame & 0x3) << 16);
	writel(reg, mfc_regs->e_gop_config);


	reg = p_vp8->profile & 0x3;
	writel(reg, mfc_regs->e_picture_profile);


	reg = readl(mfc_regs->e_rc_config);

	reg &= ~(0x1 << 8);
	reg |= ((p->rc_mb & 0x1) << 8);
	writel(reg, mfc_regs->e_rc_config);


	if (p->rc_frame && p->rc_framerate_num && p->rc_framerate_denom) {
		reg = 0;
		reg |= ((p->rc_framerate_num & 0xFFFF) << 16);
		reg |= p->rc_framerate_denom & 0xFFFF;
		writel(reg, mfc_regs->e_rc_frame_rate);
	}


	reg &= ~(0x7F);
	reg |= p_vp8->rc_frame_qp & 0x7F;
	writel(reg, mfc_regs->e_rc_config);


	writel(0x0, mfc_regs->e_fixed_picture_qp);
	if (!p->rc_frame && !p->rc_mb) {
		reg = 0;
		reg |= ((p_vp8->rc_p_frame_qp & 0x7F) << 8);
		reg |= p_vp8->rc_frame_qp & 0x7F;
		writel(reg, mfc_regs->e_fixed_picture_qp);
	}


	reg = ((p_vp8->rc_max_qp & 0x7F) << 8);

	reg |= p_vp8->rc_min_qp & 0x7F;
	writel(reg, mfc_regs->e_rc_qp_bound);


	if (p->frame_skip_mode ==
			V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT) {
		writel(p->vbv_size & 0xFFFF, mfc_regs->e_vbv_buffer_size);

		if (p->rc_frame)
			writel(p->vbv_delay, mfc_regs->e_vbv_init_delay);
	}


	reg = 0;
	reg |= (p_vp8->imd_4x4 & 0x1) << 10;
	switch (p_vp8->num_partitions) {
	case V4L2_CID_MPEG_VIDEO_VPX_1_PARTITION:
		val = 0;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_2_PARTITIONS:
		val = 2;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_4_PARTITIONS:
		val = 4;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_8_PARTITIONS:
		val = 8;
		break;
	}
	reg |= (val & 0xF) << 3;
	reg |= (p_vp8->num_ref & 0x2);
	writel(reg, mfc_regs->e_vp8_options);

	mfc_debug_leave();

	return 0;
}
