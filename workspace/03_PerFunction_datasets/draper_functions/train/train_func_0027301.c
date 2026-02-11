init( const QString& dbusPath )
{


    if ( dbusPath != "/KBookmarkManager/" && dbusPath != "/KBookmarkManager/generated")
    {
        new KBookmarkManagerAdaptor(this);
        QDBusConnection::sessionBus().registerObject( dbusPath, this );

        QDBusConnection::sessionBus().connect(QString(), dbusPath, BOOKMARK_CHANGE_NOTIFY_INTERFACE,
                                    "bookmarksChanged", this, SLOT(notifyChanged(QString,QDBusMessage)));
        QDBusConnection::sessionBus().connect(QString(), dbusPath, BOOKMARK_CHANGE_NOTIFY_INTERFACE,
                                    "bookmarkConfigChanged", this, SLOT(notifyConfigChanged()));
    }
}
