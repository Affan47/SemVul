createContextBookmark()
{
    QStringList pluginNames = Context::ContextView::self()->currentApplets();
    QStringList appletNames = Context::ContextView::self()->currentAppletNames();

    AmarokUrl url;

    url.setCommand( "context" );
    url.setArg( "applets", pluginNames.join( "," ) );

    url.setName( i18n( "Context: %1", appletNames.join( "," ) ) );

    return url;
}
