carm_handle_rw(struct carm_host *host,
				  struct carm_request *crq, int error)
{
	int pci_dir;

	VPRINTK("ENTER\n");

	if (rq_data_dir(crq->rq) == WRITE)
		pci_dir = PCI_DMA_TODEVICE;
	else
		pci_dir = PCI_DMA_FROMDEVICE;

	pci_unmap_sg(host->pdev, &crq->sg[0], crq->n_elem, pci_dir);

	carm_end_rq(host, crq, error);
}
