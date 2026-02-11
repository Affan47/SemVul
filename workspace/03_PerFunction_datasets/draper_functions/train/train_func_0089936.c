cayman_dma_vm_pad_ib(struct radeon_ib *ib)
{
	while (ib->length_dw & 0x7)
		ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0);
}
