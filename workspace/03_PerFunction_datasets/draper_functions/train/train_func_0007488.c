path_cmp(list<term *> p, const list<term *>& q, list<term*>::iterator j, bool subs, bool pref) {
	list<term *>::iterator i = p.begin();

	while(i != p.end()) {
		if(j == q.end()) return false;

		if(DEBUG)
			cout << "path_cmp: " << (*i)->to_string() << " with " << (*j)->to_string() << ": ";

		if((*i)->type == THOLE || (q.size() == 1 && (*j)->type == THOLE)) {
			if(DEBUG) cout << "Only holes!" << endl;
			return true;
		}

		if(!pref_cmp(*i,*j,subs,pref)) {
			if(DEBUG) cout << "Path does not match" << endl;
			return false;
		} else {
			if(DEBUG) cout << "Path matches" << endl;
		}

		i++;
		j++;
	}


	return j == q.end();
}
