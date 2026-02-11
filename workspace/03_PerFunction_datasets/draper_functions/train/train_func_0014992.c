invokeHelp( const QString& anchor,
                                  const QString& _appname,
                                  const QByteArray& startup_id )
{
    if (!isMainThreadActive())
        return;

    KUrl url;
    QString appname;
    QString docPath;
    if (_appname.isEmpty()) {
        appname = QCoreApplication::instance()->applicationName();
    } else
        appname = _appname;

    KService::Ptr service(KService::serviceByDesktopName(appname));
    if (service) {
        docPath = service->docPath();
    }

    if (!docPath.isEmpty()) {
        url = KUrl(KUrl("help:/"), docPath);
    } else {
        url = QString::fromLatin1("help:/%1/index.html").arg(appname);
    }

    if (!anchor.isEmpty()) {
        url.addQueryItem(QString::fromLatin1("anchor"), anchor);
    }


    if (!(url.protocol() == QLatin1String("help") || url.protocol() == QLatin1String("man") || url.protocol() == QLatin1String("info"))) {
        invokeBrowser(url.url());
        return;
    }

    QDBusInterface *iface = new QDBusInterface(QLatin1String("org.kde.khelpcenter"),
                                               QLatin1String("/KHelpCenter"),
                                               QLatin1String("org.kde.khelpcenter.khelpcenter"),
                                               QDBusConnection::sessionBus());
    if ( !iface->isValid() )
    {
        QString error;
#ifdef Q_WS_WIN

        if (kdeinitExec(QLatin1String("khelpcenter"), QStringList() << url.url(), &error, 0, startup_id))
#else
        if (startServiceByDesktopName(QLatin1String("khelpcenter"), url.url(), &error, 0, 0, startup_id, false))
#endif
        {
            KMessage::message(KMessage::Error,
                              i18n("Could not launch the KDE Help Center:\n\n%1", error),
                              i18n("Could not Launch Help Center"));
            delete iface;
	    return;
        }

        delete iface;
        iface = new QDBusInterface(QLatin1String("org.kde.khelpcenter"),
                                   QLatin1String("/KHelpCenter"),
                                   QLatin1String("org.kde.khelpcenter.khelpcenter"),
                                   QDBusConnection::sessionBus());
    }

    iface->call(QString::fromLatin1("openUrl"), url.url(), startup_id );
    delete iface;
}
