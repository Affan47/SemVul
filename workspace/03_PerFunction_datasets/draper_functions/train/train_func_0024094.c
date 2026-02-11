asd_alloc_escbs(struct asd_ha_struct *asd_ha,
			   gfp_t gfp_flags)
{
	struct asd_seq_data *seq = &asd_ha->seq;
	struct asd_ascb *escb;
	int i, escbs;

	seq->escb_arr = kmalloc(seq->num_escbs*sizeof(*seq->escb_arr),
				gfp_flags);
	if (!seq->escb_arr)
		return -ENOMEM;

	escbs = seq->num_escbs;
	escb = asd_ascb_alloc_list(asd_ha, &escbs, gfp_flags);
	if (!escb) {
		asd_printk("couldn't allocate list of escbs\n");
		goto Err;
	}
	seq->num_escbs -= escbs;
	ASD_DPRINTK("num_escbs:%d\n", seq->num_escbs);

	for (i = 0; i < seq->num_escbs; i++, escb = list_entry(escb->list.next,
							       struct asd_ascb,
							       list)) {
		seq->escb_arr[i] = escb;
		escb->scb->header.opcode = EMPTY_SCB;
	}

	return 0;
Err:
	kfree(seq->escb_arr);
	seq->escb_arr = NULL;
	return -ENOMEM;

}
