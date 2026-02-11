rhine_mii_write ( struct mii_interface *mii, unsigned int reg,
                             unsigned int data ) {
	struct rhine_nic *rhn = container_of ( mii, struct rhine_nic, mii );
	unsigned int timeout = RHINE_TIMEOUT_US;
	uint8_t cr;

	DBGC2 ( rhn, "RHINE %p MII write reg %d data 0x%04x\n",
	        rhn, reg, data );


	writeb ( reg, rhn->regs + RHINE_MII_ADDR );
	writew ( data, rhn->regs + RHINE_MII_RDWR );
	cr = readb ( rhn->regs + RHINE_MII_CR );
	writeb ( ( cr | RHINE_MII_CR_WREN ), rhn->regs + RHINE_MII_CR );


	while ( timeout-- ) {
		udelay ( 1 );
		cr = readb ( rhn->regs + RHINE_MII_CR );
		if ( ! ( cr & RHINE_MII_CR_WREN ) )
			return 0;
	}

	DBGC ( rhn, "RHINE %p MII write timeout\n", rhn );
	return -ETIMEDOUT;
}
