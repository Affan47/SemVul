dragMoveEvent( QDragMoveEvent* event )
{
    QModelIndex index = indexAt( event->pos() );
    if ( index.isValid() )
    {
        m_dropIndicator = visualRect( index );
    }
    else
    {

        index = model()->index( model()->rowCount() - 1, 0, QModelIndex() );
        m_dropIndicator = visualRect( index );
        m_dropIndicator = m_dropIndicator.translated( 0, m_dropIndicator.height() );
    }
    QListView::dragMoveEvent( event );
}
