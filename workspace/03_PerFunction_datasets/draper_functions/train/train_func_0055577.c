udc_rxfifo_read_bytes(struct udc *dev, u8 *buf, int bytes)
{
	int i, j;
	u32 tmp;

	VDBG(dev, "udc_read_bytes(): %d bytes\n", bytes);


	for (i = 0; i < bytes / UDC_DWORD_BYTES; i++)
		*((u32 *)(buf + (i<<2))) = readl(dev->rxfifo);


	if (bytes % UDC_DWORD_BYTES) {
		tmp = readl(dev->rxfifo);
		for (j = 0; j < bytes % UDC_DWORD_BYTES; j++) {
			*(buf + (i<<2) + j) = (u8)(tmp & UDC_BYTE_MASK);
			tmp = tmp >> UDC_BITS_PER_BYTE;
		}
	}

	return 0;
}
