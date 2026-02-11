rcar_thermal_irq(int irq, void *data)
{
	struct rcar_thermal_common *common = data;
	struct rcar_thermal_priv *priv;
	unsigned long flags;
	u32 status, mask;

	spin_lock_irqsave(&common->lock, flags);

	mask	= rcar_thermal_common_read(common, INTMSK);
	status	= rcar_thermal_common_read(common, STR);
	rcar_thermal_common_write(common, STR, 0x000F0F0F & mask);

	spin_unlock_irqrestore(&common->lock, flags);

	status = status & ~mask;


	rcar_thermal_for_each_priv(priv, common) {
		if (rcar_thermal_had_changed(priv, status)) {
			rcar_thermal_irq_disable(priv);
			schedule_delayed_work(&priv->work,
					      msecs_to_jiffies(300));
		}
	}

	return IRQ_HANDLED;
}
