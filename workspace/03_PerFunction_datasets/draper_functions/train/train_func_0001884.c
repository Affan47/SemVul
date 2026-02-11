apply_match(match *m) {

	if(id == m->root->id) {
		if(parent == NULL && m->get_param(999999) != NULL) {
			term *r = m->get_rule()->reactum->instantiate(m);
			if(r->type != TPAR) return r;

			parallel *rp = (parallel *) r;

			term *ht = m->get_param(999999)->instantiate(NULL);

			if(ht->type == TNIL) return rp;

			if(ht->type == TPAR)
				rp->terms.insert(((parallel *)ht)->terms.begin(), ((parallel*)ht)->terms.end());
			else
				rp->terms.insert(ht);

			return rp;
		}


		if(DEBUG) cout << "BUG: parallel::apply_match(): Found match site!" << endl;
		term *r = m->get_rule()->reactum->instantiate(m);
		if(DEBUG) cout << "Returning reactum: " << r->to_string() << endl;
		return r;
	}

	set<term *> n;

	for(set<term*>::iterator i = terms.begin(); i!=terms.end(); i++) {
		n.insert((*i)->apply_match(m));
	}

	parallel *pp = new parallel(id, n);
	pp->flatten();

	return pp;
}
