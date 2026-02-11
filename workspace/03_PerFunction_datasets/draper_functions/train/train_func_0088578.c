img_ir_suspend_timer(unsigned long arg)
{
	struct img_ir_priv *priv = (struct img_ir_priv *)arg;

	spin_lock_irq(&priv->lock);


	if ((priv->hw.quirk_suspend_irq & IMG_IR_IRQ_EDGE) ==
				img_ir_read(priv, IMG_IR_IRQ_ENABLE))
		img_ir_write(priv, IMG_IR_IRQ_ENABLE,
					priv->hw.quirk_suspend_irq);

	img_ir_write(priv, IMG_IR_CONTROL, priv->hw.reg_timings.ctrl);
	spin_unlock_irq(&priv->lock);
}
