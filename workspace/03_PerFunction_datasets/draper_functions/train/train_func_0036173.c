axi_i2s_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct axi_i2s *i2s;
	void __iomem *base;
	int ret;

	i2s = devm_kzalloc(&pdev->dev, sizeof(*i2s), GFP_KERNEL);
	if (!i2s)
		return -ENOMEM;

	platform_set_drvdata(pdev, i2s);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(base))
		return PTR_ERR(base);

	i2s->regmap = devm_regmap_init_mmio(&pdev->dev, base,
		&axi_i2s_regmap_config);
	if (IS_ERR(i2s->regmap))
		return PTR_ERR(i2s->regmap);

	i2s->clk = devm_clk_get(&pdev->dev, "axi");
	if (IS_ERR(i2s->clk))
		return PTR_ERR(i2s->clk);

	i2s->clk_ref = devm_clk_get(&pdev->dev, "ref");
	if (IS_ERR(i2s->clk_ref))
		return PTR_ERR(i2s->clk_ref);

	ret = clk_prepare_enable(i2s->clk);
	if (ret)
		return ret;

	i2s->playback_dma_data.addr = res->start + AXI_I2S_REG_TX_FIFO;
	i2s->playback_dma_data.addr_width = 4;
	i2s->playback_dma_data.maxburst = 1;

	i2s->capture_dma_data.addr = res->start + AXI_I2S_REG_RX_FIFO;
	i2s->capture_dma_data.addr_width = 4;
	i2s->capture_dma_data.maxburst = 1;

	i2s->ratnum.num = clk_get_rate(i2s->clk_ref) / 2 / AXI_I2S_BITS_PER_FRAME;
	i2s->ratnum.den_step = 1;
	i2s->ratnum.den_min = 1;
	i2s->ratnum.den_max = 64;

	i2s->rate_constraints.rats = &i2s->ratnum;
	i2s->rate_constraints.nrats = 1;

	regmap_write(i2s->regmap, AXI_I2S_REG_RESET, AXI_I2S_RESET_GLOBAL);

	ret = devm_snd_soc_register_component(&pdev->dev, &axi_i2s_component,
					 &axi_i2s_dai, 1);
	if (ret)
		goto err_clk_disable;

	ret = devm_snd_dmaengine_pcm_register(&pdev->dev, NULL, 0);
	if (ret)
		goto err_clk_disable;

	return 0;

err_clk_disable:
	clk_disable_unprepare(i2s->clk);
	return ret;
}
