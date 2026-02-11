solo_mp4e_config(struct solo_dev *solo_dev)
{
	int i;
	u32 cfg;

	solo_reg_write(solo_dev, SOLO_VE_CFG0,
		       SOLO_VE_INTR_CTRL(IRQ_LEVEL) |
		       SOLO_VE_BLOCK_SIZE(SOLO_MP4E_EXT_SIZE(solo_dev) >> 16) |
		       SOLO_VE_BLOCK_BASE(SOLO_MP4E_EXT_ADDR(solo_dev) >> 16));


	cfg = SOLO_VE_BYTE_ALIGN(2) | SOLO_VE_INSERT_INDEX
		| SOLO_VE_MOTION_MODE(0);
	if (solo_dev->type != SOLO_DEV_6010) {
		cfg |= SOLO_VE_MPEG_SIZE_H(
			(SOLO_MP4E_EXT_SIZE(solo_dev) >> 24) & 0x0f);
		cfg |= SOLO_VE_JPEG_SIZE_H(
			(SOLO_JPEG_EXT_SIZE(solo_dev) >> 24) & 0x0f);
	}
	solo_reg_write(solo_dev, SOLO_VE_CFG1, cfg);

	solo_reg_write(solo_dev, SOLO_VE_WMRK_POLY, 0);
	solo_reg_write(solo_dev, SOLO_VE_VMRK_INIT_KEY, 0);
	solo_reg_write(solo_dev, SOLO_VE_WMRK_STRL, 0);
	if (solo_dev->type == SOLO_DEV_6110)
		solo_reg_write(solo_dev, SOLO_VE_WMRK_ENABLE, 0);
	solo_reg_write(solo_dev, SOLO_VE_ENCRYP_POLY, 0);
	solo_reg_write(solo_dev, SOLO_VE_ENCRYP_INIT, 0);

	solo_reg_write(solo_dev, SOLO_VE_ATTR,
		       SOLO_VE_LITTLE_ENDIAN |
		       SOLO_COMP_ATTR_FCODE(1) |
		       SOLO_COMP_TIME_INC(0) |
		       SOLO_COMP_TIME_WIDTH(15) |
		       SOLO_DCT_INTERVAL(solo_dev->type == SOLO_DEV_6010 ? 9 : 10));

	for (i = 0; i < solo_dev->nr_chans; i++) {
		solo_reg_write(solo_dev, SOLO_VE_CH_REF_BASE(i),
			       (SOLO_EREF_EXT_ADDR(solo_dev) +
			       (i * SOLO_EREF_EXT_SIZE)) >> 16);
		solo_reg_write(solo_dev, SOLO_VE_CH_REF_BASE_E(i),
			       (SOLO_EREF_EXT_ADDR(solo_dev) +
			       ((i + 16) * SOLO_EREF_EXT_SIZE)) >> 16);
	}

	if (solo_dev->type == SOLO_DEV_6110) {
		solo_reg_write(solo_dev, SOLO_VE_COMPT_MOT, 0x00040008);
	} else {
		for (i = 0; i < solo_dev->nr_chans; i++)
			solo_reg_write(solo_dev, SOLO_VE_CH_MOT(i), 0x100);
	}
}
