em2860_ir_change_protocol(struct rc_dev *rc_dev, u64 *rc_type)
{
	struct em28xx_IR *ir = rc_dev->priv;
	struct em28xx *dev = ir->dev;


	if (*rc_type & RC_BIT_RC5) {
		dev->board.xclk |= EM28XX_XCLK_IR_RC5_MODE;
		ir->full_code = 1;
		*rc_type = RC_BIT_RC5;
	} else if (*rc_type & RC_BIT_NEC) {
		dev->board.xclk &= ~EM28XX_XCLK_IR_RC5_MODE;
		ir->full_code = 1;
		*rc_type = RC_BIT_NEC;
	} else if (*rc_type & RC_BIT_UNKNOWN) {
		*rc_type = RC_BIT_UNKNOWN;
	} else {
		*rc_type = ir->rc_type;
		return -EINVAL;
	}
	em28xx_write_reg_bits(dev, EM28XX_R0F_XCLK, dev->board.xclk,
			      EM28XX_XCLK_IR_RC5_MODE);

	ir->rc_type = *rc_type;

	return 0;
}
