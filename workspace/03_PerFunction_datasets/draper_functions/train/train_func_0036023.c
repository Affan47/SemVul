resend_cciss_cmd(ctlr_info_t *h, CommandList_struct *c)
{

	memset(c->err_info, 0, sizeof(ErrorInfo_struct));


	addQ(&h->reqQ, c);
	h->Qdepth++;
	if (h->Qdepth > h->maxQsinceinit)
		h->maxQsinceinit = h->Qdepth;

	start_io(h);
}
