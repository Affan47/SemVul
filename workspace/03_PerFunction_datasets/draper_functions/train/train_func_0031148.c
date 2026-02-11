adv7511_g_register(struct v4l2_subdev *sd, struct v4l2_dbg_register *reg)
{
	reg->size = 1;
	switch (reg->reg >> 8) {
	case 0:
		reg->val = adv7511_rd(sd, reg->reg & 0xff);
		break;
	default:
		v4l2_info(sd, "Register %03llx not supported\n", reg->reg);
		adv7511_inv_register(sd);
		break;
	}
	return 0;
}
