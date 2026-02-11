img_ir_setup_raw(struct img_ir_priv *priv)
{
	u32 irq_en;

	if (!priv->raw.rdev)
		return;


	spin_lock_irq(&priv->lock);
	irq_en = img_ir_read(priv, IMG_IR_IRQ_ENABLE);
	irq_en |= IMG_IR_IRQ_EDGE;
	img_ir_write(priv, IMG_IR_IRQ_CLEAR, IMG_IR_IRQ_EDGE);
	img_ir_write(priv, IMG_IR_IRQ_ENABLE, irq_en);
	spin_unlock_irq(&priv->lock);
}
