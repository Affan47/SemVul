dump_rels(vvec & vv) {
	for(vvec::iterator I = vv.begin(), E = vv.end(); I != E; ++I) {
		value *v = *I;

		if (!v || !v->is_rel())
			continue;

		sblog << "\n\t\t\t\t\t";
		sblog << "    rels: " << *v << " : ";
		dump_vec(v->mdef);
		sblog << " <= ";
		dump_vec(v->muse);
	}
}
