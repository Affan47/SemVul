img_ir_disable_wake(struct img_ir_priv *priv)
{
	struct img_ir_priv_hw *hw = &priv->hw;
	int ret = 0;

	spin_lock_irq(&priv->lock);
	if (hw->flags & IMG_IR_F_WAKE) {

		if (hw->flags & IMG_IR_F_FILTER) {
			img_ir_write(priv, IMG_IR_IRQ_ENABLE,
				     (hw->suspend_irqen & IMG_IR_IRQ_EDGE) |
				     IMG_IR_IRQ_DATA_MATCH);
			img_ir_write_filter(priv,
					    &hw->filters[RC_FILTER_NORMAL]);
		} else {
			img_ir_write(priv, IMG_IR_IRQ_ENABLE,
				     (hw->suspend_irqen & IMG_IR_IRQ_EDGE) |
				     IMG_IR_IRQ_DATA_VALID |
				     IMG_IR_IRQ_DATA2_VALID);
			img_ir_write_filter(priv, NULL);
		}
		img_ir_write_timings(priv, &hw->reg_timings.timings,
				     RC_FILTER_NORMAL);
		hw->mode = IMG_IR_M_NORMAL;
		ret = 1;
	}
	spin_unlock_irq(&priv->lock);
	return ret;
}
