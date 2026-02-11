createDeviceInterface(const Solid::DeviceInterface::Type &type)
{

    if (!queryDeviceInterface(type))
        return 0;

    FakeDeviceInterface *iface = 0;

    switch(type)
    {
    case Solid::DeviceInterface::GenericInterface:
        iface = new FakeGenericInterface(this);
        break;
    case Solid::DeviceInterface::Processor:
        iface = new FakeProcessor(this);
        break;
    case Solid::DeviceInterface::Block:
        iface = new FakeBlock(this);
        break;
    case Solid::DeviceInterface::StorageDrive:
        iface = new FakeStorage(this);
        break;
    case Solid::DeviceInterface::OpticalDrive:
        iface = new FakeCdrom(this);
        break;
    case Solid::DeviceInterface::StorageVolume:
        iface = new FakeVolume(this);
        break;
    case Solid::DeviceInterface::OpticalDisc:
        iface = new FakeOpticalDisc(this);
        break;
    case Solid::DeviceInterface::StorageAccess:
        iface = new FakeStorageAccess(this);
        break;
    case Solid::DeviceInterface::Camera:
        iface = new FakeCamera(this);
        break;
    case Solid::DeviceInterface::PortableMediaPlayer:
        iface = new FakePortableMediaPlayer(this);
        break;
    case Solid::DeviceInterface::NetworkInterface:
        iface = new FakeNetworkInterface(this);
        break;
    case Solid::DeviceInterface::AcAdapter:
        iface = new FakeAcAdapter(this);
        break;
    case Solid::DeviceInterface::Battery:
        iface = new FakeBattery(this);
        break;
    case Solid::DeviceInterface::Button:
        iface = new FakeButton(this);
        break;
    case Solid::DeviceInterface::AudioInterface:
        iface = new FakeAudioInterface(this);
        break;
    case Solid::DeviceInterface::DvbInterface:
        iface = new FakeDvbInterface(this);
        break;
    case Solid::DeviceInterface::Video:
        break;
    case Solid::DeviceInterface::SmartCardReader:
        iface = new FakeSmartCardReader(this);
        break;
    case Solid::DeviceInterface::SerialInterface:
        break;
    case Solid::DeviceInterface::InternetGateway:
        break;
    case Solid::DeviceInterface::NetworkShare:
        iface = new FakeNetworkShare(this);
        break;
    case Solid::DeviceInterface::Unknown:
        break;
    case Solid::DeviceInterface::Last:
        break;
    }

    if(iface)
    {
        QDBusConnection::sessionBus().registerObject(d->udi+'/'+Solid::DeviceInterface::typeToString(type), iface,
                                                      QDBusConnection::ExportNonScriptableSlots);
    }

    return iface;
}
