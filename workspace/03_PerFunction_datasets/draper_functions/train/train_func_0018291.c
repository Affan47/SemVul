set_performant_mode(ctlr_info_t *h, CommandList_struct *c)
{
	if (likely(h->transMethod & CFGTBL_Trans_Performant))
		c->busaddr |= 1 | (h->blockFetchTable[c->Header.SGList] << 1);
}
