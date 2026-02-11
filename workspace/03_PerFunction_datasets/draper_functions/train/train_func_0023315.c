indexAt( int height ) const
{


    if ( !d->treeview->model() ) return QModelIndex();
    int y = d->treeview->verticalOffset();
    QModelIndex idx = d->treeview->model()->index( 0, 0, d->treeview->rootIndex() );
    do {
        if ( y >= height ) break;
#if QT_VERSION >= 0x040300
        y += d->treeview->rowHeight( idx );
#else


        y += d->treeview->indexRowSizeHint( idx );
#endif
        idx = d->treeview->indexBelow( idx );
    } while ( idx.isValid() );
    return d->proxy->mapFromSource( idx );
}
