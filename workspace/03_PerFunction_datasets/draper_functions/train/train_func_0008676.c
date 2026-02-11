c_can_reset_ram(const struct c_can_priv *priv, bool enable)
{
	if (priv->raminit)
		priv->raminit(priv, enable);
}
