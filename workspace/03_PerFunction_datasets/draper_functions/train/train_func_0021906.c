max8997_muic_remove(struct platform_device *pdev)
{
	struct max8997_muic_info *info = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < ARRAY_SIZE(muic_irqs); i++)
		free_irq(muic_irqs[i].virq, info);
	cancel_work_sync(&info->irq_work);

	return 0;
}
