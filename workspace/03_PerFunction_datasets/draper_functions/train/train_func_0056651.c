process_phi_branch(container_node* phi, unsigned id) {
	val_set &s = live;
	for (node_iterator I = phi->begin(), E = phi->end(); I != E; ++I) {
		node *n = *I;
		if (n->is_dead())
			continue;

		value *v = n->src[id];

		if (!v->is_readonly()) {
			live_changed |= s.add_val(v);
			v->flags &= ~VLF_DEAD;
		}
	}
}
