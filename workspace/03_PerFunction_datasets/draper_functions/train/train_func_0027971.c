_k_initDeviceList()
{
    Solid::DeviceNotifier *notifier = Solid::DeviceNotifier::instance();

    connect(notifier, SIGNAL(deviceAdded(QString)),
            q, SLOT(_k_deviceAdded(QString)));
    connect(notifier, SIGNAL(deviceRemoved(QString)),
            q, SLOT(_k_deviceRemoved(QString)));


    const QList<Solid::Device> &deviceList = predicate.isValid()?
                                             Solid::Device::listFromQuery(predicate)
                                           : Solid::Device::allDevices();

    foreach(const Solid::Device &device, deviceList)
    {
        addDevice(device);
    }

    emit q->modelInitialized();
}
