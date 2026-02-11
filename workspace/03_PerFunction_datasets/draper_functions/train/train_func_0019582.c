hix5hd2_destroy_hw_desc_queue(struct hix5hd2_priv *priv)
{
	int i;

	for (i = 0; i < QUEUE_NUMS; i++) {
		if (priv->pool[i].desc) {
			dma_free_coherent(priv->dev, priv->pool[i].size,
					  priv->pool[i].desc,
					  priv->pool[i].phys_addr);
			priv->pool[i].desc = NULL;
		}
	}
}
