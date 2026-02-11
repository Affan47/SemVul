mgsl_free_frame_memory(struct mgsl_struct *info, DMABUFFERENTRY *BufferList, int Buffercount)
{
	int i;

	if ( BufferList ) {
		for ( i = 0 ; i < Buffercount ; i++ ) {
			if ( BufferList[i].virt_addr ) {
				if ( info->bus_type != MGSL_BUS_TYPE_PCI )
					dma_free_coherent(NULL, DMABUFFERSIZE, BufferList[i].virt_addr, BufferList[i].dma_addr);
				BufferList[i].virt_addr = NULL;
			}
		}
	}

}
