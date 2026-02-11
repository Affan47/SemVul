addTreeWidget( QTreeWidget *treeWidget )
{
  if ( treeWidget ) {
    connectTreeWidget( treeWidget );

    d->treeWidgets.append( treeWidget );
    setEnabled( !d->treeWidgets.isEmpty() );

    d->checkColumns();
  }
}
