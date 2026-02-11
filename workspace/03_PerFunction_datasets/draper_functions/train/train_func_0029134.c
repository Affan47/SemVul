trackActivated( const QModelIndex& idx )
{
    DEBUG_BLOCK
    m_skipAutoScroll = true;
    Actions::instance()->play( idx );


    selectionModel_setCurrentIndex( idx, QItemSelectionModel::ClearAndSelect );

    setFocus();
}
