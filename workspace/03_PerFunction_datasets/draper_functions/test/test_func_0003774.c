notifyChanged( const QString &groupAddress, const QDBusMessage &msg )
{
    kDebug() << "KBookmarkManager::notifyChanged ( "<<groupAddress<<")";
    if (!d->m_update)
        return;


    if (msg.service() != QDBusConnection::sessionBus().baseService())
       parse();


    emit changed( groupAddress, QString() );
}
