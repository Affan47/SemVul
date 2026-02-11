saa7134_resume(struct pci_dev *pci_dev)
{
	struct v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	struct saa7134_dev *dev = container_of(v4l2_dev, struct saa7134_dev, v4l2_dev);
	unsigned long flags;

	pci_set_power_state(pci_dev, PCI_D0);
	pci_restore_state(pci_dev);


	saa7134_board_init1(dev);


	if (saa7134_boards[dev->board].video_out)
		saa7134_videoport_init(dev);
	if (card_has_mpeg(dev))
		saa7134_ts_init_hw(dev);
	if (dev->remote)
		saa7134_ir_start(dev);
	saa7134_hw_enable1(dev);

	msleep(100);

	saa7134_board_init2(dev);


	saa7134_set_tvnorm_hw(dev);
	saa7134_tvaudio_setmute(dev);
	saa7134_tvaudio_setvolume(dev, dev->ctl_volume);
	saa7134_tvaudio_init(dev);
	saa7134_enable_i2s(dev);
	saa7134_hw_enable2(dev);

	saa7134_irq_video_signalchange(dev);


	spin_lock_irqsave(&dev->slock, flags);
	saa7134_buffer_requeue(dev, &dev->video_q);
	saa7134_buffer_requeue(dev, &dev->vbi_q);
	saa7134_buffer_requeue(dev, &dev->ts_q);


	dev->dmasound.dma_running = 0;


	dev->insuspend = 0;
	smp_wmb();
	saa7134_set_dmabits(dev);
	spin_unlock_irqrestore(&dev->slock, flags);

	return 0;
}
