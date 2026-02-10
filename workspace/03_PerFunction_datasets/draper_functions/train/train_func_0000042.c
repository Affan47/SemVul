mic_free_interrupts(struct mic_device *mdev, struct pci_dev *pdev)
{
	int i;

	mdev->intr_ops->disable_interrupts(mdev);
	if (mdev->irq_info.num_vectors > 1) {
		for (i = 0; i < mdev->irq_info.num_vectors; i++) {
			if (mdev->irq_info.mic_msi_map[i])
				dev_warn(&pdev->dev, "irq %d may still be in use.\n",
					 mdev->irq_info.msix_entries[i].vector);
		}
		kfree(mdev->irq_info.mic_msi_map);
		kfree(mdev->irq_info.msix_entries);
		pci_disable_msix(pdev);
	} else {
		if (pci_dev_msi_enabled(pdev)) {
			free_irq(pdev->irq, mdev);
			kfree(mdev->irq_info.mic_msi_map);
			pci_disable_msi(pdev);
		} else {
			free_irq(pdev->irq, mdev);
		}
		mic_release_callbacks(mdev);
	}
}
