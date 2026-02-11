supportedDrivers(QString protocol) const
{
    Q_D(const PortableMediaPlayer);
    return_SOLID_CALL(Ifaces::PortableMediaPlayer *, d->backendObject(), QStringList(), supportedDrivers(protocol));
}
