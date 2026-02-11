pcs_remove(struct platform_device *pdev)
{
	struct pcs_device *pcs = platform_get_drvdata(pdev);

	if (!pcs)
		return 0;

	pcs_free_resources(pcs);

	return 0;
}
