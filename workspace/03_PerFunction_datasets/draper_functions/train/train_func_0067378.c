asn1p_paramlist_free(asn1p_paramlist_t *pl) {
	if(pl) {
		if(pl->params) {
			int i = pl->params_count;
			while(i--) {
				if(pl->params[i].governor)
					asn1p_ref_free(pl->params[i].governor);
				if(pl->params[i].argument)
					free(pl->params[i].argument);
				pl->params[i].governor = 0;
				pl->params[i].argument = 0;
			}
			free(pl->params);
			pl->params = 0;
		}

		free(pl);
	}
}
