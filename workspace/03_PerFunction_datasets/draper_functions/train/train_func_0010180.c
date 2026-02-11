loadBackends()
{
    QString solidFakeXml(QString::fromLocal8Bit(qgetenv("SOLID_FAKEHW")));

    if (!solidFakeXml.isEmpty()) {
        m_backends << new Solid::Backends::Fake::FakeManager(0, solidFakeXml);
    } else {
#        if defined(Q_OS_MAC)
            m_backends << new Solid::Backends::IOKit::IOKitManager(0);

#        elif defined(Q_WS_WIN) && defined(WITH_SOLID_WMI) && !defined(_WIN32_WCE)
            m_backends << new Solid::Backends::Wmi::WmiManager(0);
#        elif defined(Q_WS_WIN) && !defined(_WIN32_WCE)
            m_backends << new Solid::Backends::Win::WinDeviceManager(0);
#        elif defined(Q_OS_UNIX) && !defined(Q_OS_LINUX)
            m_backends << new Solid::Backends::Hal::HalManager(0);

#        elif defined(Q_OS_LINUX)
            bool solidHalLegacyEnabled
                = QString::fromLocal8Bit(qgetenv("SOLID_HAL_LEGACY")).toInt()==1;
            if (solidHalLegacyEnabled) {
                m_backends << new Solid::Backends::Hal::HalManager(0);
            } else {
#               if defined(UDEV_FOUND)
                    m_backends << new Solid::Backends::UDev::UDevManager(0);
#               endif
#		if defined(WITH_SOLID_UDISKS2)
                m_backends << new Solid::Backends::UDisks2::Manager(0)
#		else
                m_backends << new Solid::Backends::UDisks::UDisksManager(0)
#		endif
                           << new Solid::Backends::UPower::UPowerManager(0)
                           << new Solid::Backends::Fstab::FstabManager(0);
            }
#        endif

#        if defined (HUPNP_FOUND)
            m_backends << new Solid::Backends::UPnP::UPnPDeviceManager(0);
#        endif
    }
}
