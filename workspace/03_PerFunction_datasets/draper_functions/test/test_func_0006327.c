getFrequencyCutoff(int n) const
{
    switch (n) {
    case 0: return m_freq0;
    case 1: return m_freq1;
    case 2: return m_freq2;
    }
    return 0.f;
}
