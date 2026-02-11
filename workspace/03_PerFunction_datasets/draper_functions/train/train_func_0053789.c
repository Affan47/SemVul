era_sieve (nsieve_t *ns, char *vals){


	for (int skip=2; skip < (int) (sqrt(ns->fb_bound) + 1); skip++){
		if (vals[skip-2] == 1){
			continue;
		}
		for (int pos=2*skip; pos < ns->fb_bound; pos += skip){
			vals[pos-2] = 1;
		}
	}
}
