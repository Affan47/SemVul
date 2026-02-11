removeSlaveOnHold()
{
    kDebug(7006) << m_slaveOnHold;
    if (m_slaveOnHold) {
        m_slaveOnHold->kill();
    }
    m_slaveOnHold = 0;
    m_urlOnHold.clear();
}
