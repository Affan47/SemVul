mlx5_core_event(struct mlx5_core_dev *dev, enum mlx5_dev_event event,
		     unsigned long param)
{
	struct mlx5_priv *priv = &dev->priv;
	struct mlx5_device_context *dev_ctx;
	unsigned long flags;

	spin_lock_irqsave(&priv->ctx_lock, flags);

	list_for_each_entry(dev_ctx, &priv->ctx_list, list)
		if (dev_ctx->intf->event)
			dev_ctx->intf->event(dev, dev_ctx->context, event, param);

	spin_unlock_irqrestore(&priv->ctx_lock, flags);
}
