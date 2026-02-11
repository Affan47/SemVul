dragEnterEvent( QDragEnterEvent* event )
{
  #ifndef HIDE_RADIO
    QString url = event->mimeData()->urls().value( 0 ).toString();
    if ( url.startsWith( "lastfm://" ) )
    {
        event->acceptProposedAction();
    }
    else
        event->ignore();
  #endif
}
