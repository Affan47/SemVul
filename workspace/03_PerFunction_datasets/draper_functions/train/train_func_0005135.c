cx8802_cancel_buffers(struct cx8802_dev *dev)
{
	dprintk( 1, "cx8802_cancel_buffers" );
	cx8802_stop_dma(dev);
	do_cancel_buffers(dev);
}
