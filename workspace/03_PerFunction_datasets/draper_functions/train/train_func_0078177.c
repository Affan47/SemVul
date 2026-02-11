pipe_change(struct m66592 *m66592, u16 pipenum)
{
	struct m66592_ep *ep = m66592->pipenum2ep[pipenum];
	unsigned short mbw;

	if (ep->use_dma)
		return;

	m66592_mdfy(m66592, pipenum, M66592_CURPIPE, ep->fifosel);

	ndelay(450);

	if (m66592->pdata->on_chip)
		mbw = M66592_MBW_32;
	else
		mbw = M66592_MBW_16;

	m66592_bset(m66592, mbw, ep->fifosel);
}
