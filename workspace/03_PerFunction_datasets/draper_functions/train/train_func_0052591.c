alx_intr_legacy(int irq, void *data)
{
	struct alx_priv *alx = data;
	struct alx_hw *hw = &alx->hw;
	u32 intr;

	intr = alx_read_mem32(hw, ALX_ISR);

	if (intr & ALX_ISR_DIS || !(intr & alx->int_mask))
		return IRQ_NONE;

	return alx_intr_handle(alx, intr);
}
