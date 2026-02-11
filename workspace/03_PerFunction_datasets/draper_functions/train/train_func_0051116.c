hpsa_allocate_ioaccel2_sg_chain_blocks(struct ctlr_info *h)
{
	int i;

	if (h->chainsize <= 0)
		return 0;

	h->ioaccel2_cmd_sg_list =
		kzalloc(sizeof(*h->ioaccel2_cmd_sg_list) * h->nr_cmds,
					GFP_KERNEL);
	if (!h->ioaccel2_cmd_sg_list)
		return -ENOMEM;
	for (i = 0; i < h->nr_cmds; i++) {
		h->ioaccel2_cmd_sg_list[i] =
			kmalloc(sizeof(*h->ioaccel2_cmd_sg_list[i]) *
					h->maxsgentries, GFP_KERNEL);
		if (!h->ioaccel2_cmd_sg_list[i])
			goto clean;
	}
	return 0;

clean:
	hpsa_free_ioaccel2_sg_chain_blocks(h);
	return -ENOMEM;
}
