mic_msi_irq_info_show(struct seq_file *s, void *pos)
{
	struct mic_device *mdev  = s->private;
	int reg;
	int i, j;
	u16 entry;
	u16 vector;
	struct pci_dev *pdev = mdev->pdev;

	if (pci_dev_msi_enabled(pdev)) {
		for (i = 0; i < mdev->irq_info.num_vectors; i++) {
			if (pdev->msix_enabled) {
				entry = mdev->irq_info.msix_entries[i].entry;
				vector = mdev->irq_info.msix_entries[i].vector;
			} else {
				entry = 0;
				vector = pdev->irq;
			}

			reg = mdev->intr_ops->read_msi_to_src_map(mdev, entry);

			seq_printf(s, "%s %-10d %s %-10d MXAR[%d]: %08X\n",
				   "IRQ:", vector, "Entry:", entry, i, reg);

			seq_printf(s, "%-10s", "offset:");
			for (j = (MIC_NUM_OFFSETS - 1); j >= 0; j--)
				seq_printf(s, "%4d ", j);
			seq_puts(s, "\n");


			seq_printf(s, "%-10s", "count:");
			for (j = (MIC_NUM_OFFSETS - 1); j >= 0; j--)
				seq_printf(s, "%4d ",
					   (mdev->irq_info.mic_msi_map[i] &
					   BIT(j)) ? 1 : 0);
			seq_puts(s, "\n\n");
		}
	} else {
		seq_puts(s, "MSI/MSIx interrupts not enabled\n");
	}

	return 0;
}
