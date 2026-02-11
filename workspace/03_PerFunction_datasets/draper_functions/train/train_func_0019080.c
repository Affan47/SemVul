keyPressEvent( QKeyEvent *event )
{
    switch( event->key() )
    {
        case Qt::Key_Delete:
            slotDelete();
            return;

        case Qt::Key_F2:
            slotRename();
            return;
    }
    QTreeView::keyPressEvent( event );
}
