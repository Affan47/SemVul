mapToSource( const QModelIndex &index ) const
{

    if( !index.isValid() )
        return m_rootIndex;

    if( isGroup( index ) )
    {

        return m_rootIndex;
    }

    QModelIndex proxyParent = index.parent();

    QModelIndex originalParent = mapToSource( proxyParent );

    int originalRow = index.row();
    if( originalParent == m_rootIndex )
    {
        int indexInGroup = index.row();
        if( !proxyParent.isValid() )
            indexInGroup -= m_groupMaps.count();

        QList<int> childRows = m_groupHash.value( proxyParent.row() );
        if( childRows.isEmpty() || indexInGroup >= childRows.count() || indexInGroup < 0 )
            return QModelIndex();

        originalRow = childRows.at( indexInGroup );

    }
    return sourceModel()->index( originalRow, index.column(), originalParent );
}
