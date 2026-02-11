ichx_read_bit(int reg, unsigned nr)
{
	unsigned long flags;
	u32 data;
	int reg_nr = nr / 32;
	int bit = nr & 0x1f;

	spin_lock_irqsave(&ichx_priv.lock, flags);

	data = ICHX_READ(ichx_priv.desc->regs[reg][reg_nr],
			 ichx_priv.gpio_base);

	if (reg == GPIO_LVL && ichx_priv.desc->use_outlvl_cache)
		data = ichx_priv.outlvl_cache[reg_nr] | data;

	spin_unlock_irqrestore(&ichx_priv.lock, flags);

	return data & (1 << bit) ? 1 : 0;
}
