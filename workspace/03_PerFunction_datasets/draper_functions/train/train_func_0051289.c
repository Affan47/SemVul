setCurrentIndex( const QModelIndex &index )
{
    QModelIndex indexCopy = model()->index( index.row(), index.column() );
    QListView::setCurrentIndex( indexCopy );
}
