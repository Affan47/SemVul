xgene_enet_shutdown(struct platform_device *pdev)
{
	struct xgene_enet_pdata *pdata;

	pdata = platform_get_drvdata(pdev);
	if (!pdata)
		return;

	if (!pdata->ndev)
		return;

	xgene_enet_remove(pdev);
}
