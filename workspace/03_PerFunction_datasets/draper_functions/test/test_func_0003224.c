imx_wm8962_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	struct imx_wm8962_data *data = snd_soc_card_get_drvdata(card);

	if (!IS_ERR(data->codec_clk))
		clk_disable_unprepare(data->codec_clk);

	return 0;
}
