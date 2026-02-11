bcmgenet_hfb_add_filter(struct bcmgenet_priv *priv, u32 *f_data,
			    u32 f_length, u32 rx_queue)
{
	int f_index;
	u32 i;

	f_index = bcmgenet_hfb_find_unused_filter(priv);
	if (f_index < 0)
		return -ENOMEM;

	if (f_length > priv->hw_params->hfb_filter_size)
		return -EINVAL;

	for (i = 0; i < f_length; i++)
		bcmgenet_hfb_writel(priv, f_data[i],
			(f_index * priv->hw_params->hfb_filter_size + i) *
			sizeof(u32));

	bcmgenet_hfb_set_filter_length(priv, f_index, 2 * f_length);
	bcmgenet_hfb_set_filter_rx_queue_mapping(priv, f_index, rx_queue);
	bcmgenet_hfb_enable_filter(priv, f_index);
	bcmgenet_hfb_reg_writel(priv, 0x1, HFB_CTRL);

	return 0;
}
