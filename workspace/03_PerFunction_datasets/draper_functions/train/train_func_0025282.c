load_matched_font(AWEOps *ops, SFInfo *sf, LoadList *request)
{
	int i, rc;
	int found = 0;
	LoadList req;

	for (i = 0; i < sf->npresets; i++) {
		if (request->pat.preset != -1 &&
		    sf->preset[i].preset != request->pat.preset)
			continue;
		if (request->pat.bank != -1 &&
		    sf->preset[i].bank != request->pat.bank)
			continue;
		req = *request;
		if (req.pat.preset == -1)
			req.pat.preset = sf->preset[i].preset;
		if (req.pat.bank == -1)
			req.pat.bank = sf->preset[i].bank;

		awe_merge_keys(&request->map, &req.pat, &req.map);
		rc = load_samples(ops, sf, i, &req, NULL);
		if (rc == AWE_RET_ERR || rc == AWE_RET_NOMEM)
			return rc;
		else if (rc == AWE_RET_SKIP)
			continue;
		rc = load_infos(ops, sf, i, &req, NULL);
		if (rc == AWE_RET_ERR || rc == AWE_RET_NOMEM)
			return rc;
		found++;
	}
	if (found)
		return AWE_RET_OK;
	else
		return AWE_RET_SKIP;
}
