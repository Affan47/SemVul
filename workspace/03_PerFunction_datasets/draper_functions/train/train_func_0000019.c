reset()
{
    if (m_threaded) {
        m_threadSetMutex.lock();
        for (set<ProcessThread *>::iterator i = m_threadSet.begin();
             i != m_threadSet.end(); ++i) {
            if (m_debugLevel > 0) {
                cerr << "RubberBandStretcher::~RubberBandStretcher: joining (channel " << *i << ")" << endl;
            }
            (*i)->abandon();
            (*i)->wait();
            delete *i;
        }
        m_threadSet.clear();
    }

    for (size_t c = 0; c < m_channels; ++c) {
        m_channelData[c]->reset();
    }

    m_mode = JustCreated;
    if (m_phaseResetAudioCurve) m_phaseResetAudioCurve->reset();
    if (m_stretchAudioCurve) m_stretchAudioCurve->reset();
    if (m_silentAudioCurve) m_silentAudioCurve->reset();
    m_inputDuration = 0;
    m_silentHistory = 0;

    if (m_threaded) m_threadSetMutex.unlock();

    reconfigure();
}
