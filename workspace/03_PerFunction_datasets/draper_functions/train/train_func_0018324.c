start_io(ctlr_info_t *h)
{
	CommandList_struct *c;

	while (!list_empty(&h->reqQ)) {
		c = list_entry(h->reqQ.next, CommandList_struct, list);

		if ((h->access.fifo_full(h))) {
			dev_warn(&h->pdev->dev, "fifo full\n");
			break;
		}


		removeQ(c);
		h->Qdepth--;


		h->access.submit_command(h, c);


		addQ(&h->cmpQ, c);
	}
}
