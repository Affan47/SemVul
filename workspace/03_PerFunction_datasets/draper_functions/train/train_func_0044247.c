tc3589x_set_bits(struct tc3589x *tc3589x, u8 reg, u8 mask, u8 val)
{
	int ret;

	mutex_lock(&tc3589x->lock);

	ret = tc3589x_reg_read(tc3589x, reg);
	if (ret < 0)
		goto out;

	ret &= ~mask;
	ret |= val;

	ret = tc3589x_reg_write(tc3589x, reg, ret);

out:
	mutex_unlock(&tc3589x->lock);
	return ret;
}
