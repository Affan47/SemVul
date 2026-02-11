slotSetFilter( const QString &filter )
{
    if( m_treeModel && m_treeModel->currentFilter() != filter )
        m_treeModel->setCurrentFilter( filter );
}
