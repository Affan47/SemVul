add_child(const NodeRef& node) {

    node_debug ( get_name() << ": " << "add_child(" << node->get_name() << ")" );

	if (m_impl->has_child(node->get_name())) {
		throw Exception( NODE_DUP_CHILD, node->get_name() );
	}
    if (node->m_impl->m_parent) {
        throw Exception( NODE_LINKED, node->get_name() );
    }
    if(this == &(*node)) {
        throw Exception ( NODE_SELFREF, node->get_name() );
    }

	m_impl->m_children.push_back(node);
	m_impl->m_childrenmap[node->get_name()] = m_impl->m_children.size()-1;
    node->m_impl->m_parent = this;
}
