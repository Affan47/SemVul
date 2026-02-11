asn1p_paramlist_clone(asn1p_paramlist_t *pl) {
	asn1p_paramlist_t *newpl;

	newpl = asn1p_paramlist_new(pl->_lineno);
	if(newpl) {
		int i;
		for(i = 0; i < pl->params_count; i++) {
			if(asn1p_paramlist_add_param(newpl,
				pl->params[i].governor,
				pl->params[i].argument
			)) {
				asn1p_paramlist_free(newpl);
				newpl = NULL;
				break;
			}
		}
	}

	return newpl;
}
