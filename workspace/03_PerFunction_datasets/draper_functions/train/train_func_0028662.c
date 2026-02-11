FIFOInit(FIFO * fifo)
{
        u32 i;

	fifo->begin = 0;
        fifo->end = 0;
        for(i = 0; i<0x8000; ++i)
        	fifo->data[i] = 0;
        fifo->full = FALSE;
        fifo->empty = TRUE;
        fifo->error = FALSE;
}
