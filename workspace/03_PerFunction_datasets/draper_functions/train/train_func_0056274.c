alloc_vda_req(struct esas2r_adapter *a,
			  struct esas2r_request *rq)
{
	struct esas2r_mem_desc *memdesc = kzalloc(
		sizeof(struct esas2r_mem_desc), GFP_KERNEL);

	if (memdesc == NULL) {
		esas2r_hdebug("could not alloc mem for vda request memdesc\n");
		return false;
	}

	memdesc->size = sizeof(union atto_vda_req) +
			ESAS2R_DATA_BUF_LEN;

	if (!esas2r_initmem_alloc(a, memdesc, 256)) {
		esas2r_hdebug("could not alloc mem for vda request\n");
		kfree(memdesc);
		return false;
	}

	a->num_vrqs++;
	list_add(&memdesc->next_desc, &a->vrq_mds_head);

	rq->vrq_md = memdesc;
	rq->vrq = (union atto_vda_req *)memdesc->virt_addr;
	rq->vrq->scsi.handle = a->num_vrqs;

	return true;
}
