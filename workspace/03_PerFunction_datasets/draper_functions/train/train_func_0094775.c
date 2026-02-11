transform(VariableDecl* node) {
	if (node->hasAssignment()) {
		node->setAssignment(static_cast<Assignment*>(
			node->getAssignment()->accept(*this))
		);
	}

	return node;
}
