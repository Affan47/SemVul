SMprobe(PROBETYPE type, TOKEN *token, void *value) {
    struct artngnum	*ann;
    ARTHANDLE		*art;

    switch (type) {
    case SELFEXPIRE:
	return (method_data[typetoindex[token->type]].selfexpire);
    case SMARTNGNUM:
	if (method_data[typetoindex[token->type]].initialized == INIT_FAIL) {
	    SMseterror(SMERR_UNINIT, NULL);
	    return false;
	}
	if (method_data[typetoindex[token->type]].initialized == INIT_NO && !InitMethod(typetoindex[token->type])) {
	    SMseterror(SMERR_UNINIT, NULL);
	    warn("SM: can't probe article with uninitialized method");
	    return false;
	}
	if ((ann = (struct artngnum *)value) == NULL)
	    return false;
	ann->groupname = NULL;
	if (storage_methods[typetoindex[token->type]].ctl(type, token, value)) {
	    if (ann->artnum != 0) {

		return true;
	    } else {
		art = storage_methods[typetoindex[token->type]].retrieve(*token, RETR_HEAD);
		if (art == NULL) {
		    if (ann->groupname != NULL)
			free(ann->groupname);
		    storage_methods[typetoindex[token->type]].freearticle(art);
		    return false;
		}
		if ((ann->groupname = GetXref(art)) == NULL) {
		    if (ann->groupname != NULL)
			free(ann->groupname);
		    storage_methods[typetoindex[token->type]].freearticle(art);
		    return false;
		}
		storage_methods[typetoindex[token->type]].freearticle(art);
		if ((ann->artnum = GetGroups(ann->groupname)) == 0) {
		    if (ann->groupname != NULL)
			free(ann->groupname);
		    return false;
		}
		return true;
	    }
	} else {
	    return false;
	}
    case EXPENSIVESTAT:
	return (method_data[typetoindex[token->type]].expensivestat);
    default:
	return false;
    }
}
