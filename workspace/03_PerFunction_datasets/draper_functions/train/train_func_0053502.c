img_ir_clk_notify(struct notifier_block *self, unsigned long action,
			     void *data)
{
	struct img_ir_priv *priv = container_of(self, struct img_ir_priv,
						hw.clk_nb);
	switch (action) {
	case POST_RATE_CHANGE:
		img_ir_change_frequency(priv, data);
		break;
	default:
		break;
	}
	return NOTIFY_OK;
}
