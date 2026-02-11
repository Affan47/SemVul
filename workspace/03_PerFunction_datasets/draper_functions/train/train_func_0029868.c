add_view_tolist(struct dumpcontext *dctx, dns_view_t *view) {
	struct viewlistentry *vle;
	isc_result_t result = ISC_R_SUCCESS;


	for (vle = ISC_LIST_HEAD(dctx->viewlist);
	     vle != NULL;
	     vle = ISC_LIST_NEXT(vle, link))
		if (vle->view == view)
			return (ISC_R_SUCCESS);

	vle = isc_mem_get(dctx->mctx, sizeof *vle);
	if (vle == NULL)
		return (ISC_R_NOMEMORY);
	vle->view = NULL;
	dns_view_attach(view, &vle->view);
	ISC_LINK_INIT(vle, link);
	ISC_LIST_INIT(vle->zonelist);
	ISC_LIST_APPEND(dctx->viewlist, vle, link);
	if (dctx->dumpzones)
		result = dns_zt_apply(view->zonetable, ISC_TRUE,
				      add_zone_tolist, dctx);
	return (result);
}
