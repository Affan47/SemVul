reg_delay ( struct forcedeth_private *priv, int offset, u32 mask,
	    u32 target, int delay, int delaymax, const char *msg )
{
	void *ioaddr = priv->mmio_addr;

	pci_push ( ioaddr );
	do {
		udelay ( delay );
		delaymax -= delay;
		if ( delaymax < 0 ) {
			if ( msg )
				DBG ( "%s\n", msg );
			return 1;
		}
	} while ( ( readl ( ioaddr + offset ) & mask ) != target );

	return 0;
}
