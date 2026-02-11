fsl_esai_shutdown(struct snd_pcm_substream *substream,
			      struct snd_soc_dai *dai)
{
	struct fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);

	if (!IS_ERR(esai_priv->fsysclk))
		clk_disable_unprepare(esai_priv->fsysclk);
	if (!IS_ERR(esai_priv->extalclk))
		clk_disable_unprepare(esai_priv->extalclk);
	clk_disable_unprepare(esai_priv->coreclk);
}
