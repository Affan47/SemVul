accept(Visitor& visitor) {
	NodeList::iterator node(m_nodes.begin()), end(m_nodes.end());
	while (node != end) {
		(*node)->accept(visitor);
		++node;
	}
}
