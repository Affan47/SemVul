setAccelCTRL4()
{
    unsigned char ctrl4;

    switch (m_settings->m_GD20M303DLHCAccelFsr) {
    case LSM303DLHC_ACCEL_FSR_2:
        m_accelScale = (RTFLOAT)0.001 / (RTFLOAT)64;
        break;

    case LSM303DLHC_ACCEL_FSR_4:
        m_accelScale = (RTFLOAT)0.002 / (RTFLOAT)64;
        break;

    case LSM303DLHC_ACCEL_FSR_8:
        m_accelScale = (RTFLOAT)0.004 / (RTFLOAT)64;
        break;

    case LSM303DLHC_ACCEL_FSR_16:
        m_accelScale = (RTFLOAT)0.012 / (RTFLOAT)64;
        break;

    default:
        HAL_ERROR1("Illegal LSM303DLHC accel FSR code %d\n", m_settings->m_GD20M303DLHCAccelFsr);
        return false;
    }

    ctrl4 = (m_settings->m_GD20M303DLHCAccelFsr << 4);

    return m_settings->HALWrite(m_accelSlaveAddr,  LSM303DLHC_CTRL2_A, ctrl4, "Failed to set LSM303DLHC CTRL4");
}
