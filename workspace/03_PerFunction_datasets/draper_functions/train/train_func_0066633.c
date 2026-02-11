slotRemoveService(DNSSD::RemoteService::Ptr service)
{
    kDebug();
    emit q->remoteAppletUnannounced(services[service->serviceName()]);
    services.remove(service->serviceName());
    zeroconfServices.remove(service->serviceName());
}
