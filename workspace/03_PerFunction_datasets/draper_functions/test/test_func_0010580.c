select_free_selectop(struct selectop *sop)
{
	if (sop->event_readset_in)
		mm_free(sop->event_readset_in);
	if (sop->event_writeset_in)
		mm_free(sop->event_writeset_in);
	if (sop->event_readset_out)
		mm_free(sop->event_readset_out);
	if (sop->event_writeset_out)
		mm_free(sop->event_writeset_out);

	memset(sop, 0, sizeof(struct selectop));
	mm_free(sop);
}
