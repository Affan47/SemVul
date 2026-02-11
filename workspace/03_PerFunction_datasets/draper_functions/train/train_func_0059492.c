solo_s_jpeg_qp(struct solo_dev *solo_dev, unsigned int ch,
		    unsigned int qp)
{
	unsigned long flags;
	unsigned int idx, reg;

	if ((ch > 31) || (qp > 3))
		return;

	if (solo_dev->type == SOLO_DEV_6010)
		return;

	if (ch < 16) {
		idx = 0;
		reg = SOLO_VE_JPEG_QP_CH_L;
	} else {
		ch -= 16;
		idx = 1;
		reg = SOLO_VE_JPEG_QP_CH_H;
	}
	ch *= 2;

	spin_lock_irqsave(&solo_dev->jpeg_qp_lock, flags);

	solo_dev->jpeg_qp[idx] &= ~(3 << ch);
	solo_dev->jpeg_qp[idx] |= (qp & 3) << ch;

	solo_reg_write(solo_dev, reg, solo_dev->jpeg_qp[idx]);

	spin_unlock_irqrestore(&solo_dev->jpeg_qp_lock, flags);
}
