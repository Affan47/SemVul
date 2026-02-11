pcnet32_irq_disable ( struct pcnet32_private *priv )
{
	unsigned long ioaddr = priv->pci_dev->ioaddr;

	DBGP ( "pcnet32_irq_disable\n" );

	priv->a->write_csr ( ioaddr, 0, 0x0000 );

	priv->irq_enabled = 0;
}
