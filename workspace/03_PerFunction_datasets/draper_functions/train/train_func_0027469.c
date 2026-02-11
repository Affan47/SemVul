lookupHost(const QString& hostName, unsigned long timeout)
{

    QHostAddress address (hostName);
    QHostInfo hostInfo;
    if (!address.isNull()) {
        QList<QHostAddress> addressList;
        addressList << address;
        hostInfo.setAddresses(addressList);
        return hostInfo;
    }


    hostInfo = HostInfo::lookupCachedHostInfoFor(hostName);
    if (!hostInfo.hostName().isEmpty() && hostInfo.error() == QHostInfo::NoError) {
        return hostInfo;
    }


    QSharedPointer<NameLookupThreadRequest> request = QSharedPointer<NameLookupThreadRequest>(new NameLookupThreadRequest(hostName));
    nameLookUpThread->semaphore()->acquire();
    nameLookUpThread->semaphore()->release();
    QMetaObject::invokeMethod(nameLookUpThread->worker(), "lookupHost", Qt::QueuedConnection, Q_ARG(QSharedPointer<NameLookupThreadRequest>, request));
    if (request->semaphore()->tryAcquire(1, timeout)) {
        hostInfo = request->result();
        if (!hostInfo.hostName().isEmpty() && hostInfo.error() == QHostInfo::NoError) {
            HostInfo::cacheLookup(hostInfo);
        }
    } else {
        QMetaObject::invokeMethod(nameLookUpThread->worker(), "abortLookup", Qt::QueuedConnection, Q_ARG(QSharedPointer<NameLookupThreadRequest>, request));
    }


    return hostInfo;
}
