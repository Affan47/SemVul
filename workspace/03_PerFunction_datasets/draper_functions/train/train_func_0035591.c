slotEdit( const QModelIndex &index )
{


    edit( m_proxyModel->mapFromSource( index ) );
}
