teardown()
{
    if (m_teardownInProgress || m_setupInProgress || !isAccessible()) {
        return false;
    }
    m_teardownInProgress = true;
    m_device->broadcastActionRequested("teardown");

    if (m_device->prop("info.interfaces").toStringList().contains("org.freedesktop.Hal.Device.Volume.Crypto")) {
        return callCryptoTeardown();
    } else if (FstabHandling::isInFstab(m_device->prop("block.device").toString())) {
        return callSystemUnmount();
    } else {
        return callHalVolumeUnmount();
    }
}
