free_pdev(struct pcifront_device *pdev)
{
	dev_dbg(&pdev->xdev->dev, "freeing pdev @ 0x%p\n", pdev);

	pcifront_free_roots(pdev);

	cancel_work_sync(&pdev->op_work);

	if (pdev->irq >= 0)
		unbind_from_irqhandler(pdev->irq, pdev);

	if (pdev->evtchn != INVALID_EVTCHN)
		xenbus_free_evtchn(pdev->xdev, pdev->evtchn);

	if (pdev->gnt_ref != INVALID_GRANT_REF)
		gnttab_end_foreign_access(pdev->gnt_ref, 0 ,
					  (unsigned long)pdev->sh_info);
	else
		free_page((unsigned long)pdev->sh_info);

	dev_set_drvdata(&pdev->xdev->dev, NULL);

	kfree(pdev);
}
