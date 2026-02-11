mdc_dma_remove(struct platform_device *pdev)
{
	struct mdc_dma *mdma = platform_get_drvdata(pdev);
	struct mdc_chan *mchan, *next;

	of_dma_controller_free(pdev->dev.of_node);
	dma_async_device_unregister(&mdma->dma_dev);

	list_for_each_entry_safe(mchan, next, &mdma->dma_dev.channels,
				 vc.chan.device_node) {
		list_del(&mchan->vc.chan.device_node);

		synchronize_irq(mchan->irq);
		devm_free_irq(&pdev->dev, mchan->irq, mchan);

		tasklet_kill(&mchan->vc.task);
	}

	clk_disable_unprepare(mdma->clk);

	return 0;
}
