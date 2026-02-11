addChild( ConstraintNode* nc, int idx )
{
    if ( !m_children.contains( nc ) ) {
        if ( idx <= m_children.size() ) {
            m_children.insert( idx, nc );
        } else {
            m_children.append( nc );
        }
        return true;
    } else {
        debug() << "Tried to add a node that's already a child";
        return false;
    }
}
