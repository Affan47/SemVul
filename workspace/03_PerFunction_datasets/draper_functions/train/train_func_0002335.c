cx25821_irq(int irq, void *dev_id)
{
	struct cx25821_dev *dev = dev_id;
	u32 pci_status;
	u32 vid_status;
	int i, handled = 0;
	u32 mask[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

	pci_status = cx_read(PCI_INT_STAT);

	if (pci_status == 0)
		goto out;

	for (i = 0; i < VID_CHANNEL_NUM; i++) {
		if (pci_status & mask[i]) {
			vid_status = cx_read(dev->channels[i].
				sram_channels->int_stat);

			if (vid_status)
				handled += cx25821_video_irq(dev, i,
						vid_status);

			cx_write(PCI_INT_STAT, mask[i]);
		}
	}

out:
	return IRQ_RETVAL(handled);
}
