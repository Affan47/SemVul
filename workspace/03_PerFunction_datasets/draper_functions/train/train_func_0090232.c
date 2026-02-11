moveDown( const QString &layout )
{
    int index = m_layoutNames.indexOf( layout );
    if ( index < m_layoutNames.size() -1 ) {
        m_layoutNames.swap ( index, index + 1 );
        emit( layoutListChanged() );
        storeLayoutOrdering();
        return index + 1;
    }

    return index;
}
