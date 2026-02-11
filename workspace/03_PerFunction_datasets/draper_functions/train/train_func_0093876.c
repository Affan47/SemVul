usbhs_fifo_probe(struct usbhs_priv *priv)
{
	struct usbhs_fifo *fifo;


	fifo = usbhsf_get_cfifo(priv);
	fifo->name	= "CFIFO";
	fifo->port	= CFIFO;
	fifo->sel	= CFIFOSEL;
	fifo->ctr	= CFIFOCTR;


	USBHS_DFIFO_INIT(priv, fifo, 0);
	USBHS_DFIFO_INIT(priv, fifo, 1);
	USBHS_DFIFO_INIT_NO_PORT(priv, fifo, 2);
	USBHS_DFIFO_INIT_NO_PORT(priv, fifo, 3);

	return 0;
}
