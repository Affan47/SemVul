setAccelCTRL1()
{
    unsigned char ctrl1;

    if ((m_settings->m_LSM9DS0AccelSampleRate < 0) || (m_settings->m_LSM9DS0AccelSampleRate > 10)) {
        HAL_ERROR1("Illegal LSM9DS0 accel sample rate code %d\n", m_settings->m_LSM9DS0AccelSampleRate);
        return false;
    }

    ctrl1 = (m_settings->m_LSM9DS0AccelSampleRate << 4) | 0x07;

    return m_settings->HALWrite(m_accelCompassSlaveAddr,  LSM9DS0_CTRL1, ctrl1, "Failed to set LSM9DS0 accell CTRL1");
}
