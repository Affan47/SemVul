forwardUnsource(const BodyNodeP& n, bool add) {
	for (const NodeId* x = n.node->heads(); x != n.node->heads_end() && graph_->getAtomNode(*x).scc == n.node->scc; ++x) {
		if (atoms_[*x].hasSource() && atoms_[*x].watch() == n.id) {
			atoms_[*x].markSourceInvalid();
			sourceQ_.push_back(*x);
		}
		if (add && atoms_[*x].watch() == n.id) {
			enqueueTodo(*x);
		}
	}
}
