setVolume(int volume)
{
    m_volume = volume;
    if (m_volume > MIX_MAX_VOLUME) {
        m_volume = MIX_MAX_VOLUME;
    }
    else if (m_volume < 0) {
        m_volume = 0;
    }
}
