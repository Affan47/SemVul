dropEvent( QDropEvent* event )
{
    QList<QUrl> urls = event->mimeData()->urls();
    if ( urls.isEmpty() )
        return;

    QString fileName = urls.first().toLocalFile();
    if ( fileName.isEmpty() )
        return;

    loadFile( fileName );
}
