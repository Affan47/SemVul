ismt_dev_init(struct ismt_priv *priv)
{

	priv->hw = dmam_alloc_coherent(&priv->pci_dev->dev,
				       (ISMT_DESC_ENTRIES
					       * sizeof(struct ismt_desc)),
				       &priv->io_rng_dma,
				       GFP_KERNEL);
	if (!priv->hw)
		return -ENOMEM;

	memset(priv->hw, 0, (ISMT_DESC_ENTRIES * sizeof(struct ismt_desc)));

	priv->head = 0;
	init_completion(&priv->cmp);

	return 0;
}
