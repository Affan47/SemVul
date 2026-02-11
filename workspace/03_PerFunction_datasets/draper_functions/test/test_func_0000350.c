ssb_chipco_gpio_pulldown(struct ssb_chipcommon *cc, u32 mask, u32 value)
{
	unsigned long flags;
	u32 res = 0;

	if (cc->dev->id.revision < 20)
		return 0xffffffff;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = chipco_write32_masked(cc, SSB_CHIPCO_GPIOPULLDOWN, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	return res;
}
