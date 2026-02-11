tea5764_mute(struct tea5764_device *radio, int on)
{
	struct tea5764_regs *r = &radio->regs;
	int tnctrl = r->tnctrl;

	if (on)
		r->tnctrl |= TEA5764_TNCTRL_MU;
	else
		r->tnctrl &= ~TEA5764_TNCTRL_MU;
	if (tnctrl != r->tnctrl)
		tea5764_i2c_write(radio);
}
