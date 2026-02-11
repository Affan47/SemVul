pipe_change(struct r8a66597 *r8a66597, u16 pipenum)
{
	struct r8a66597_ep *ep = r8a66597->pipenum2ep[pipenum];

	if (ep->use_dma)
		r8a66597_bclr(r8a66597, DREQE, ep->fifosel);

	r8a66597_mdfy(r8a66597, pipenum, CURPIPE, ep->fifosel);

	ndelay(450);

	if (r8a66597_is_sudmac(r8a66597) && ep->use_dma)
		r8a66597_bclr(r8a66597, mbw_value(r8a66597), ep->fifosel);
	else
		r8a66597_bset(r8a66597, mbw_value(r8a66597), ep->fifosel);

	if (ep->use_dma)
		r8a66597_bset(r8a66597, DREQE, ep->fifosel);
}
