contextMenuEvent( QContextMenuEvent *event )
{
    QModelIndex clickedIdx = indexAt( event->pos() );

    QModelIndexList indices;
    if( clickedIdx.isValid() && selectedIndexes().contains( clickedIdx ) )
        indices << selectedIndexes();
    else if( clickedIdx.isValid() )
        indices << clickedIdx;

    QActionList actions = actionsFor( indices );
    if( actions.isEmpty() )
    {
        resetActionTargets();
        return;
    }

    KMenu menu;
    foreach( QAction *action, actions )
        menu.addAction( action );
    menu.exec( mapToGlobal( event->pos() ) );


    resetActionTargets();
}
