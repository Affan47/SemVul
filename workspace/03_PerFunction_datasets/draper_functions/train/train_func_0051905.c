IMUInit()
{
    unsigned char result;

#ifdef GD20HM303D_CACHE_MODE
    m_firstTime = true;
    m_cacheIn = m_cacheOut = m_cacheCount = 0;
#endif


    m_imuData.fusionPoseValid = false;
    m_imuData.fusionQPoseValid = false;
    m_imuData.gyroValid = true;
    m_imuData.accelValid = true;
    m_imuData.compassValid = true;
    m_imuData.pressureValid = false;
    m_imuData.temperatureValid = false;
    m_imuData.humidityValid = false;


    m_gyroSlaveAddr = m_settings->m_I2CSlaveAddress;
    if (m_gyroSlaveAddr == L3GD20H_ADDRESS0)
        m_accelCompassSlaveAddr = LSM303D_ADDRESS0;
    else
        m_accelCompassSlaveAddr = LSM303D_ADDRESS1;

    setCalibrationData();


    if (!m_settings->HALOpen())
        return false;


    if (!m_settings->HALWrite(m_gyroSlaveAddr, L3GD20H_LOW_ODR, 0x04, "Failed to reset L3GD20"))
        return false;

    if (!m_settings->HALWrite(m_gyroSlaveAddr, L3GD20H_CTRL5, 0x80, "Failed to boot L3GD20"))
        return false;

    if (!m_settings->HALRead(m_gyroSlaveAddr, L3GD20H_WHO_AM_I, 1, &result, "Failed to read L3GD20H id"))
        return false;

    if (result != L3GD20H_ID) {
        HAL_ERROR1("Incorrect L3GD20H id %d\n", result);
        return false;
    }

    if (!setGyroSampleRate())
            return false;

    if (!setGyroCTRL2())
            return false;

    if (!setGyroCTRL4())
            return false;


    if (!m_settings->HALRead(m_accelCompassSlaveAddr, LSM303D_WHO_AM_I, 1, &result, "Failed to read LSM303D id"))
        return false;

    if (result != LSM303D_ID) {
        HAL_ERROR1("Incorrect LSM303D id %d\n", result);
        return false;
    }

    if (!setAccelCTRL1())
        return false;

    if (!setAccelCTRL2())
        return false;

    if (!setCompassCTRL5())
        return false;

    if (!setCompassCTRL6())
        return false;

    if (!setCompassCTRL7())
        return false;

#ifdef GD20HM303D_CACHE_MODE


    if (!m_settings->HALWrite(m_gyroSlaveAddr, L3GD20H_FIFO_CTRL, 0x3f, "Failed to set L3GD20H FIFO mode"))
        return false;
#endif

    if (!setGyroCTRL5())
            return false;

    gyroBiasInit();

    HAL_INFO("GD20HM303D init complete\n");
    return true;
}
