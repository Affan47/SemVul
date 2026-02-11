devicesFromQuery(const QString &parentUdi, Solid::DeviceInterface::Type type)
{
    if (!parentUdi.isEmpty())
    {
        QStringList found = findDeviceStringMatch(QLatin1String("parent"), parentUdi);

        if (type == Solid::DeviceInterface::Unknown)
        {
            return found;
        }

        QStringList result;

        QStringList::ConstIterator it = found.constBegin();
        QStringList::ConstIterator end = found.constEnd();

        for (; it!=end; ++it)
        {
            FakeDevice *device = d->loadedDevices[*it];

            if (device->queryDeviceInterface(type))
            {
                result << *it;
            }
        }

        return result;
    }
    else if(type != Solid::DeviceInterface::Unknown)
    {
        return findDeviceByDeviceInterface(type);
    }
    else
    {
        return allDevices();
    }
}
