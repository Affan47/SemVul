bg_names(parsenode *p) {
	if(!p) return vector<name>();

	switch(p->type) {
		case NODE_NAME: {
			vector<name> v;
			name nm = bigraph::name_from_string(((namenode *)p)->to_string());
			v.push_back(nm);
			return v;
		}
		case NODE_SEQ: {
			return bg_names((seqnode *) p);
		}
		default:
			cerr << "BUG: Invalid name: " << p->to_string() << endl;
			exit(1);
			break;
	}

	return vector<name>();
}
