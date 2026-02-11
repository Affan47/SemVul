dw_mci_hi6220_parse_dt(struct dw_mci *host)
{
	struct k3_priv *priv;

	priv = devm_kzalloc(host->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->reg = syscon_regmap_lookup_by_phandle(host->dev->of_node,
					 "hisilicon,peripheral-syscon");
	if (IS_ERR(priv->reg))
		priv->reg = NULL;

	host->priv = priv;
	return 0;
}
