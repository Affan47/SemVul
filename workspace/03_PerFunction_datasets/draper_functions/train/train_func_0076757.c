parse_inst_layers(AWEOps *ops, SFInfo *sf, LayerTable *tbl, LoadList *request,
			     LoadList *exlist, Loader loader, int level)
{
	SFInstHdr *inst;
	int rc, i, nlayers;
	SFGenLayer *lay, *globalp;

	if (level >= 2) {
		fprintf(stderr, "parse_layer: too deep instrument level\n");
		return AWE_RET_ERR;
	}


	if (!tbl->set[SF_instrument])
		return AWE_RET_SKIP;


	inst = &sf->inst[tbl->val[SF_instrument]];


	if ((nlayers = inst->hdr.nlayers) <= 0 ||
	    (lay = inst->hdr.layer) == NULL)
		return AWE_RET_SKIP;


	globalp = NULL;
	if (is_global(lay)) {
		globalp = lay;
		lay++;
		nlayers--;
	}


	for (i = 0; i < nlayers; i++, lay++) {
		LayerTable ctbl;
		clear_table(&ctbl);
		if (globalp)
			set_to_table(sf, &ctbl, globalp, P_GLOBAL);
		set_to_table(sf, &ctbl, lay, P_LAYER);

		if (!ctbl.set[SF_sampleId]) {

			merge_table(sf, &ctbl, tbl);
			if (! sanity_range(&ctbl))
				continue;
			rc = parse_inst_layers(ops, sf, &ctbl, request, exlist,
					       loader, level+1);
			if (rc == AWE_RET_NOMEM || rc == AWE_RET_ERR)
				return rc;
		} else {
			init_and_merge_table(sf, &ctbl, tbl);
			if (! sanity_range(&ctbl))
				continue;
			if (request->pat.keynote != -1 &&
			    ! in_range(&ctbl, request->pat.keynote))
				continue;
			if (exlist) {

				SFPatchRec tmp;
				tmp = request->pat;
				tmp.keynote = LOWNUM(tbl->val[SF_keyRange]);
				if (is_excluded_preset(exlist, &tmp))
					continue;
			}

			rc = loader(ops, sf, &ctbl, request);
			if (rc == AWE_RET_NOMEM || rc == AWE_RET_ERR)
				return rc;
		}
	}
	return AWE_RET_OK;
}
