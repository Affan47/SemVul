types( Mode mode )
{
    QStringList imagetypes;
    const KService::List services = KServiceTypeTrader::self()->query("QImageIOPlugins");
    foreach(const KService::Ptr &service, services) {
        if ( (service->property("X-KDE-Read").toBool() && mode == Reading) ||
             (service->property("X-KDE-Write").toBool() && mode == Writing ) ) {

            imagetypes += service->property("X-KDE-ImageFormat").toStringList();
        }
    }
    return imagetypes;
}
