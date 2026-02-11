operator=( const NodeRef &copy ) {
    if ( this != &copy ) {
        dec();
        m_node = copy.m_node;
        if (m_node) {
           m_node->m_impl->inc();
           node_debug ( "Inc ref: " << m_node->get_name() << " refs: " << m_node->m_impl->m_ref_count );
        }
    }
    return *this;
}
