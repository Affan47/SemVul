nvme_setup_io_queues(struct nvme_dev *dev)
{
	struct nvme_queue *adminq = dev->queues[0];
	struct pci_dev *pdev = to_pci_dev(dev->dev);
	int result, i, vecs, nr_io_queues, size;

	nr_io_queues = num_possible_cpus();
	result = nvme_set_queue_count(&dev->ctrl, &nr_io_queues);
	if (result < 0)
		return result;


	if (result > 0) {
		dev_err(dev->ctrl.device,
			"Could not set queue count (%d)\n", result);
		return 0;
	}

	if (dev->cmb && NVME_CMB_SQS(dev->cmbsz)) {
		result = nvme_cmb_qdepth(dev, nr_io_queues,
				sizeof(struct nvme_command));
		if (result > 0)
			dev->q_depth = result;
		else
			nvme_release_cmb(dev);
	}

	size = db_bar_size(dev, nr_io_queues);
	if (size > 8192) {
		iounmap(dev->bar);
		do {
			dev->bar = ioremap(pci_resource_start(pdev, 0), size);
			if (dev->bar)
				break;
			if (!--nr_io_queues)
				return -ENOMEM;
			size = db_bar_size(dev, nr_io_queues);
		} while (1);
		dev->dbs = dev->bar + 4096;
		adminq->q_db = dev->dbs;
	}


	free_irq(dev->entry[0].vector, adminq);


	if (pdev->msi_enabled)
		pci_disable_msi(pdev);
	else if (pdev->msix_enabled)
		pci_disable_msix(pdev);

	for (i = 0; i < nr_io_queues; i++)
		dev->entry[i].entry = i;
	vecs = pci_enable_msix_range(pdev, dev->entry, 1, nr_io_queues);
	if (vecs < 0) {
		vecs = pci_enable_msi_range(pdev, 1, min(nr_io_queues, 32));
		if (vecs < 0) {
			vecs = 1;
		} else {
			for (i = 0; i < vecs; i++)
				dev->entry[i].vector = i + pdev->irq;
		}
	}


	nr_io_queues = vecs;
	dev->max_qid = nr_io_queues;

	result = queue_request_irq(dev, adminq, adminq->irqname);
	if (result) {
		adminq->cq_vector = -1;
		goto free_queues;
	}


	nvme_free_queues(dev, nr_io_queues + 1);
	return nvme_create_io_queues(dev);

 free_queues:
	nvme_free_queues(dev, 1);
	return result;
}
