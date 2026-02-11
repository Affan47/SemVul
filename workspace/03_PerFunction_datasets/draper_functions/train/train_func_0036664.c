ov965x_set_flip(struct ov965x *ov965x)
{
	u8 mvfp = 0;

	if (ov965x->ctrls.hflip->val)
		mvfp |= MVFP_MIRROR;

	if (ov965x->ctrls.vflip->val)
		mvfp |= MVFP_FLIP;

	return ov965x_write(ov965x->client, REG_MVFP, mvfp);
}
