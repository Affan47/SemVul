isAlsaControl(const char* lastElement)
{
    if (sscanf (lastElement, "controlC%d", &m_cardnum) == 1) {
        m_deviceFile = m_device->property("DEVNAME").toString();
        m_name = cardNumberToName();
        m_driver = Solid::AudioInterface::Alsa;
        m_type = Solid::AudioInterface::AudioControl;
        return true;
    }
    return false;
}
