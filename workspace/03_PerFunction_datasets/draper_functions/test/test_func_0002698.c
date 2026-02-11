qib_create_ctxtdata(struct qib_pportdata *ppd, u32 ctxt,
	int node_id)
{
	struct qib_devdata *dd = ppd->dd;
	struct qib_ctxtdata *rcd;

	rcd = kzalloc_node(sizeof(*rcd), GFP_KERNEL, node_id);
	if (rcd) {
		INIT_LIST_HEAD(&rcd->qp_wait_list);
		rcd->node_id = node_id;
		rcd->ppd = ppd;
		rcd->dd = dd;
		rcd->cnt = 1;
		rcd->ctxt = ctxt;
		dd->rcd[ctxt] = rcd;
#ifdef CONFIG_DEBUG_FS
		if (ctxt < dd->first_user_ctxt) {
			rcd->opstats = kzalloc_node(sizeof(*rcd->opstats),
				GFP_KERNEL, node_id);
			if (!rcd->opstats) {
				kfree(rcd);
				qib_dev_err(dd,
					"Unable to allocate per ctxt stats buffer\n");
				return NULL;
			}
		}
#endif
		dd->f_init_ctxt(rcd);


		rcd->rcvegrbuf_size = 0x8000;
		rcd->rcvegrbufs_perchunk =
			rcd->rcvegrbuf_size / dd->rcvegrbufsize;
		rcd->rcvegrbuf_chunks = (rcd->rcvegrcnt +
			rcd->rcvegrbufs_perchunk - 1) /
			rcd->rcvegrbufs_perchunk;
		BUG_ON(!is_power_of_2(rcd->rcvegrbufs_perchunk));
		rcd->rcvegrbufs_perchunk_shift =
			ilog2(rcd->rcvegrbufs_perchunk);
	}
	return rcd;
}
