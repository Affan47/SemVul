s5p_mfc_set_enc_params_h263(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	struct s5p_mfc_enc_params *p = &ctx->enc_params;
	struct s5p_mfc_mpeg4_enc_params *p_h263 = &p->codec.mpeg4;
	unsigned int reg;
	unsigned int shm;

	s5p_mfc_set_enc_params(ctx);

	if (!p->rc_frame) {
		shm = s5p_mfc_read_info_v5(ctx, P_B_FRAME_QP);
		shm &= ~(0xFFF);
		shm |= (p_h263->rc_p_frame_qp & 0x3F);
		s5p_mfc_write_info_v5(ctx, shm, P_B_FRAME_QP);
	}

	if (p->rc_frame && p->rc_framerate_denom)
		mfc_write(dev, p->rc_framerate_num * 1000
			/ p->rc_framerate_denom, S5P_FIMV_ENC_RC_FRAME_RATE);
	else
		mfc_write(dev, 0, S5P_FIMV_ENC_RC_FRAME_RATE);

	reg = mfc_read(dev, S5P_FIMV_ENC_RC_CONFIG);

	reg &= ~(0x3F);
	reg |= p_h263->rc_frame_qp;
	mfc_write(dev, reg, S5P_FIMV_ENC_RC_CONFIG);

	reg = mfc_read(dev, S5P_FIMV_ENC_RC_QBOUND);

	reg &= ~(0x3F << 8);
	reg |= (p_h263->rc_max_qp << 8);

	reg &= ~(0x3F);
	reg |= p_h263->rc_min_qp;
	mfc_write(dev, reg, S5P_FIMV_ENC_RC_QBOUND);

	shm = s5p_mfc_read_info_v5(ctx, EXT_ENC_CONTROL);

	if (p->frame_skip_mode ==
			V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT) {
		shm &= ~(0xFFFF << 16);
		shm |= (p->vbv_size << 16);
	}
	s5p_mfc_write_info_v5(ctx, shm, EXT_ENC_CONTROL);
	return 0;
}
