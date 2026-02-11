_k_initDeviceList()
{
    Solid::DeviceNotifier *notifier = Solid::DeviceNotifier::instance();

    connect(notifier, SIGNAL(deviceAdded(QString)),
            q, SLOT(_k_deviceAdded(QString)));
    connect(notifier, SIGNAL(deviceRemoved(QString)),
            q, SLOT(_k_deviceRemoved(QString)));

    const QList<Solid::Device> &deviceList = Solid::Device::listFromQuery(predicate);

    foreach(const Solid::Device &device, deviceList) {
        availableDevices << device.udi();
    }

    _k_reloadBookmarks();
}
