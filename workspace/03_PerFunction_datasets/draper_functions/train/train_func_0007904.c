pcnet32_hw_start ( struct pcnet32_private *priv )
{
	unsigned long ioaddr = priv->pci_dev->ioaddr;
	int i;


	priv->a->write_csr ( ioaddr, 0, Init );


	i = 0;
	while ( i++ < 100 )
		if ( priv->a->read_csr ( ioaddr, 0 ) & InitDone )
			break;


	priv->a->write_csr ( ioaddr, 0, Strt );
}
