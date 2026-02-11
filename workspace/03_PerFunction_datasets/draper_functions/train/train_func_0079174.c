ichx_write_bit(int reg, unsigned nr, int val, int verify)
{
	unsigned long flags;
	u32 data, tmp;
	int reg_nr = nr / 32;
	int bit = nr & 0x1f;
	int ret = 0;

	spin_lock_irqsave(&ichx_priv.lock, flags);

	if (reg == GPIO_LVL && ichx_priv.desc->use_outlvl_cache)
		data = ichx_priv.outlvl_cache[reg_nr];
	else
		data = ICHX_READ(ichx_priv.desc->regs[reg][reg_nr],
				 ichx_priv.gpio_base);

	if (val)
		data |= 1 << bit;
	else
		data &= ~(1 << bit);
	ICHX_WRITE(data, ichx_priv.desc->regs[reg][reg_nr],
			 ichx_priv.gpio_base);
	if (reg == GPIO_LVL && ichx_priv.desc->use_outlvl_cache)
		ichx_priv.outlvl_cache[reg_nr] = data;

	tmp = ICHX_READ(ichx_priv.desc->regs[reg][reg_nr],
			ichx_priv.gpio_base);
	if (verify && data != tmp)
		ret = -EPERM;

	spin_unlock_irqrestore(&ichx_priv.lock, flags);

	return ret;
}
