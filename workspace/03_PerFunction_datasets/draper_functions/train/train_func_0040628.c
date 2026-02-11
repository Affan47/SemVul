skge_rx_setup(struct skge_port *skge __unused,
			  struct skge_element *e,
			  struct io_buffer *iob, unsigned int bufsize)
{
	struct skge_rx_desc *rd = e->desc;
	u64 map;

	map = ( iob != NULL ) ? virt_to_bus(iob->data) : 0;

	rd->dma_lo = map;
	rd->dma_hi = map >> 32;
	e->iob = iob;
	rd->csum1_start = ETH_HLEN;
	rd->csum2_start = ETH_HLEN;
	rd->csum1 = 0;
	rd->csum2 = 0;

	wmb();

	rd->control = BMU_OWN | BMU_STF | BMU_IRQ_EOF | BMU_TCP_CHECK | bufsize;
}
