loadStaticPlugins(QHash<QString, QGeoServiceProviderFactory*> *plugins)
{
#if !defined QT_NO_DEBUG
    const bool showDebug = qgetenv("QT_DEBUG_PLUGINS").toInt() > 0;
#endif

    QObjectList staticPlugins = QPluginLoader::staticInstances();
    for (int i = 0; i < staticPlugins.count(); ++i) {
        QGeoServiceProviderFactory *f = qobject_cast<QGeoServiceProviderFactory*>(staticPlugins.at(i));
        if (f) {
            QString name = f->providerName();

#if !defined QT_NO_DEBUG
            if (showDebug)
                qDebug() << "Static: found a service provider plugin with name" << name;
#endif
            if (!name.isEmpty()) {
                plugins->insertMulti(name, f);
            }
        }

    }
}
