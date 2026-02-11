preorder_string(parallel *t) {
	set<term *> ch = t->get_children();
	list<st_el*> sorted_ch;
	list<st_el*> res;

	for(set<term *>::iterator i = ch.begin(); i!=ch.end(); i++) {
		switch((*i)->type) {
		case TPREF:
			sorted_ch.push_back(
				new st_el(*i,bigraph::control_to_string(
					((prefix *)(*i))->get_control()) + fports(((prefix *)(*i))->get_ports())));
			break;
		case THOLE:
			sorted_ch.push_back(new st_el(*i, "[-]"));
			break;
		case TNUM:
			sorted_ch.push_back(new st_el(*i, (*i)->to_string()));
			break;
		case TNIL:
			break;
		}
	}

	sorted_ch.sort(cmp_st_elp);

	for(list<st_el*>::iterator i = sorted_ch.begin(); i!=sorted_ch.end(); i++) {
		list<st_el*> j = preorder_string((*i)->data);
		res.insert(res.end(), j.begin(), j.end());
	}


	return res;
}
