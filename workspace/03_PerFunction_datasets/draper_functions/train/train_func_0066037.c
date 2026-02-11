newAccelCalData(const RTVector3& data)
{

    for (int i = 0; i < 3; i++) {
        if (m_accelCalEnable[i]) {
            m_averageValue.setData(i, (data.data(i) * ACCEL_ALPHA + m_averageValue.data(i) * (1.0 - ACCEL_ALPHA)));
            if (m_accelMin.data(i) > m_averageValue.data(i))
                m_accelMin.setData(i, m_averageValue.data(i));
            if (m_accelMax.data(i) < m_averageValue.data(i))
                m_accelMax.setData(i, m_averageValue.data(i));
        }
    }
}
