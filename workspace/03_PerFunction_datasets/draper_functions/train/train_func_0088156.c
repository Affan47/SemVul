transform(NodeArray* node) {
	NodeList nlist(node->getNodes());
	NodeList::iterator cur(nlist.begin()), end(nlist.end());

	node->getNodes().clear();

	while (cur != end) {
		*cur = (*cur)->accept(*this);

		if (*cur) {
			node->append(*cur);
		}

		++cur;
	}

	return node;
}
