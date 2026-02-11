deleteSubtree( const QModelIndex& _idx )
{
    QModelIndex idx = dataIndex( _idx );
    if ( !idx.model() ) return;
    const QModelIndex parent( idx.parent() );
    const int colcount = idx.model()->columnCount( parent );
    {for ( int i = 0; i < colcount; ++i ) {
        removeItem( parent.child( idx.row(), i ) );
    }}
    const int rowcount = summaryHandlingModel()->rowCount( _idx );
    {for ( int i = 0; i < rowcount; ++i ) {
        deleteSubtree( summaryHandlingModel()->index( i, summaryHandlingModel()->columnCount(_idx)-1, _idx ) );
    }}
}
