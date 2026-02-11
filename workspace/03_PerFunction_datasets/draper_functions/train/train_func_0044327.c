supportedDrivers(QString protocol) const
{
    QStringList drivers;

    if (m_device->propertyExists("ID_USB_DRIVER"))
        drivers << m_device->property("ID_USB_DRIVER").toString();

    if (protocol == QLatin1String("video4linux")) {
        drivers << QLatin1String("video4linux");
        if (m_device->property("ID_V4L_VERSION").toInt() == 2) {
            drivers << QLatin1String("video4linux2");
        } else {
            drivers << QLatin1String("video4linux1");
        }
    }
    return drivers;
}
