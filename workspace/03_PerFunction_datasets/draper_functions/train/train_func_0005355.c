i82092aa_pci_remove(struct pci_dev *dev)
{
	int i;

	enter("i82092aa_pci_remove");

	free_irq(dev->irq, i82092aa_interrupt);

	for (i = 0; i < socket_count; i++)
		pcmcia_unregister_socket(&sockets[i].socket);

	leave("i82092aa_pci_remove");
}
