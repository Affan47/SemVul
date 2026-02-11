adv7511_s_register(struct v4l2_subdev *sd, const struct v4l2_dbg_register *reg)
{
	switch (reg->reg >> 8) {
	case 0:
		adv7511_wr(sd, reg->reg & 0xff, reg->val & 0xff);
		break;
	default:
		v4l2_info(sd, "Register %03llx not supported\n", reg->reg);
		adv7511_inv_register(sd);
		break;
	}
	return 0;
}
