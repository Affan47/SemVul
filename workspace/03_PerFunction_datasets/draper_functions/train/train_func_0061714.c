asd_unbuild_smp_ascb(struct asd_ascb *a)
{
	struct sas_task *task = a->uldd_task;

	BUG_ON(!task);
	pci_unmap_sg(a->ha->pcidev, &task->smp_task.smp_req, 1,
		     PCI_DMA_TODEVICE);
	pci_unmap_sg(a->ha->pcidev, &task->smp_task.smp_resp, 1,
		     PCI_DMA_FROMDEVICE);
}
