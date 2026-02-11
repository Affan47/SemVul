icon() const
{
    if (parentUdi().isEmpty()) {
        return QLatin1String("computer");
    }

    if (queryDeviceInterface(Solid::DeviceInterface::Processor)) {
        return QLatin1String("cpu");
    } else if (queryDeviceInterface(Solid::DeviceInterface::PortableMediaPlayer)) {

        return QLatin1String("multimedia-player");
    } else if (queryDeviceInterface(Solid::DeviceInterface::Camera)) {
        return QLatin1String("camera-photo");
    } else if (queryDeviceInterface(Solid::DeviceInterface::Video)) {
        return QLatin1String("camera-web");
    } else if (queryDeviceInterface(Solid::DeviceInterface::AudioInterface)) {
        const AudioInterface audioIface(const_cast<UDevDevice *>(this));
        switch (audioIface.soundcardType()) {
        case Solid::AudioInterface::InternalSoundcard:
            return QLatin1String("audio-card");
        case Solid::AudioInterface::UsbSoundcard:
            return QLatin1String("audio-card-usb");
        case Solid::AudioInterface::FirewireSoundcard:
            return QLatin1String("audio-card-firewire");
        case Solid::AudioInterface::Headset:
            if (udi().contains("usb", Qt::CaseInsensitive) ||
                    audioIface.name().contains("usb", Qt::CaseInsensitive)) {
                return QLatin1String("audio-headset-usb");
            } else {
                return QLatin1String("audio-headset");
            }
        case Solid::AudioInterface::Modem:
            return QLatin1String("modem");
        }
    } else if (queryDeviceInterface(Solid::DeviceInterface::SerialInterface)) {


        return QLatin1String("modem");
    }

    return QString();
}
