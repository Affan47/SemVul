getLatency() const
{
    if (!m_realtime) return 0;
    return int((m_windowSize/2) / m_pitchScale + 1);
}
