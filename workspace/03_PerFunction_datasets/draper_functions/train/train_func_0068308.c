cx8802_fini_common(struct cx8802_dev *dev)
{
	dprintk( 2, "cx8802_fini_common\n" );
	cx8802_stop_dma(dev);
	pci_disable_device(dev->pci);


	free_irq(dev->pci->irq, dev);
}
