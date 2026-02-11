findPrevious( const QString & searchTerm, int fields )
{
    DEBUG_BLOCK
    QList<int> selected = selectedRows();

    bool updateProxy = false;
    if ( ( The::playlist()->currentSearchFields() != fields ) || ( The::playlist()->currentSearchTerm() != searchTerm ) )
        updateProxy = true;

    int currentRow = model()->rowCount();
    if( selected.size() > 0 )
        currentRow = selected.first();

    int row = The::playlist()->findPrevious( searchTerm, currentRow, fields );
    if( row != -1 )
    {


        QModelIndex index = model()->index( row, 0 );
        QItemSelection selItems( index, index );
        selectionModel()->select( selItems, QItemSelectionModel::SelectCurrent );

        QModelIndex foundIndex = model()->index( row, 0, QModelIndex() );
        setCurrentIndex( foundIndex );
        if ( foundIndex.isValid() )
            scrollTo( foundIndex, QAbstractItemView::PositionAtCenter );

        emit( found() );
    }
    else
        emit( notFound() );

    if ( updateProxy )
        The::playlist()->filterUpdated();
}
