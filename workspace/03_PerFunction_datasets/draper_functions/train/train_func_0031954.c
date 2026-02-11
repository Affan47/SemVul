contextMenuEvent( QContextMenuEvent* e )
{
    QModelIndexList selection = selectionModel()->selectedIndexes();

    if ( selection.count() == 1 ) {
        QMenu menu( this );

        menu.addAction( QIcon( ":/icons/rename-16.png" ), tr( "&Rename" ), this, SLOT( renameItem() ) );
        menu.addAction( QIcon( ":/icons/delete-16.png" ), tr( "&Delete" ), this, SLOT( deleteItem() ) );

        menu.exec( e->globalPos() );
    }
}
