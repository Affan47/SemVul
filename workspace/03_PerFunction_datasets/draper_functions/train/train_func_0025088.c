_k_deviceRemoved(const QString &udi)
{
    if (availableDevices.contains(udi)) {
        availableDevices.remove(udi);
        _k_reloadBookmarks();
    }
}
