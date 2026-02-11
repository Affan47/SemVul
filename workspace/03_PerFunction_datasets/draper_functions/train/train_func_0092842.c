setApplicationId( const QString& desktop )
    {
    if( desktop.startsWith( '/' ))
        {
        d->application_id = desktop;
        return;
        }

    QString desk = KStandardDirs::locate( "apps", desktop );
    if( desk.isEmpty())
        desk = KStandardDirs::locate( "services", desktop );
    if( desk.isEmpty())
        return;
    d->application_id = desk;
    }
