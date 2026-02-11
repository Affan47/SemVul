mlx4_en_get_num_flows(struct mlx4_en_priv *priv)
{

	int i, res = 0;
	for (i = 0; i < MAX_NUM_OF_FS_RULES; i++) {
		if (priv->ethtool_rules[i].id)
			res++;
	}
	return res;

}
