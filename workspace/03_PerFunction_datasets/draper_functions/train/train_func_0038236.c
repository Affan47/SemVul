setSource(const AtomNodeP& head, const BodyNodeP& body) {
	assert(!solver_->isFalse(body.node->lit));


	if (!atoms_[head.id].hasSource() && !solver_->isFalse(head.node->lit)) {
		updateSource(atoms_[head.id], body);
		sourceQ_.push_back(head.id);
	}
}
