slotChanged()
{
    if (m_device) {
        const bool old_isPlugged = m_isPlugged;
        updateCache();

        if (old_isPlugged != m_isPlugged)
        {
            emit plugStateChanged(m_isPlugged, m_device.data()->udi());
        }
    }
}
