deletePortMapping(const QString& remoteHost, qint16 externalPort, const NetworkProtocol& mappingProtocol)
{
    Q_D(const InternetGateway);

    SOLID_CALL(Ifaces::InternetGateway*, d->backendObject(),
               deletePortMapping(remoteHost, externalPort, mappingProtocol));
}
