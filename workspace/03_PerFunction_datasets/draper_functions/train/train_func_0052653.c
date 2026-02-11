ChannelSelect(Mushware::U32& outChannel)
{
    bool found = false;
    Mushware::U32 numChannels = m_channelDefs.size();

    for (U32 i=0; i<numChannels && !found; ++i)
    {
        const MediaAudioChannelDef& defRef = ChannelDef(m_nextChannel);
        if (defRef.Activity() == MediaAudioChannelDef::kActivityIdle)
        {
            outChannel = m_nextChannel;
            found = true;
        }
        ++m_nextChannel;
        if (m_nextChannel >= numChannels)
        {
            m_nextChannel = 0;
        }
    }
    return found;
}
