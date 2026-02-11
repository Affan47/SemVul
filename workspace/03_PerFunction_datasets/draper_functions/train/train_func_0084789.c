snd_malloc_dev_iram(struct snd_dma_buffer *dmab, size_t size)
{
	struct device *dev = dmab->dev.dev;
	struct gen_pool *pool = NULL;

	dmab->area = NULL;
	dmab->addr = 0;

	if (dev->of_node)
		pool = of_gen_pool_get(dev->of_node, "iram", 0);

	if (!pool)
		return;


	dmab->private_data = pool;

	dmab->area = gen_pool_dma_alloc(pool, size, &dmab->addr);
}
