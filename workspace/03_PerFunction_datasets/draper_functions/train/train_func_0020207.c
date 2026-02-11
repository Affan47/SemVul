launchUrl( QAction *action )
{
    KUrl url = KUrl( action->data().toString() );
    KRun::runUrl( url, "text/html", 0, false );
}
