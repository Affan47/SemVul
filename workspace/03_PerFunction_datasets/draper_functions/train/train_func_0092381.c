init_args(bool repl) {
	alu_node *p = static_cast<alu_node*>(first);
	assert(p->is_valid());
	while (p) {
		dst.insert(dst.end(), p->dst.begin(), p->dst.end());
		src.insert(src.end(), p->src.begin(), p->src.end());
		p = static_cast<alu_node*>(p->next);
	}

	value *replicated_value = NULL;

	for (vvec::iterator I = dst.begin(), E = dst.end(); I != E; ++I) {
		value *v = *I;
		if (v) {
			if (repl) {
				if (replicated_value)
					v->assign_source(replicated_value);
				else
					replicated_value = v;
			}

			v->def = this;
		}
	}
}
