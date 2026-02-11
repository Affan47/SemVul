bcmgenet_hfb_find_unused_filter(struct bcmgenet_priv *priv)
{
	u32 f_index;

	for (f_index = 0; f_index < priv->hw_params->hfb_filter_cnt; f_index++)
		if (!bcmgenet_hfb_is_filter_enabled(priv, f_index))
			return f_index;

	return -ENOMEM;
}
