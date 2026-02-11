getVideoPacket()
{
    bool framesAvailable = true;
    bool frameDecoded = false;

    int attempts = 0;

    if (m_pPacket)
    {
        av_free_packet(m_pPacket);
        delete m_pPacket;
    }

    m_pPacket = new AVPacket();

    while (framesAvailable && !frameDecoded && (attempts++ < 1000))
    {
        framesAvailable = av_read_frame(m_pFormatContext, m_pPacket) >= 0;
        if (framesAvailable)
        {
            frameDecoded = m_pPacket->stream_index == m_VideoStream;
            if (!frameDecoded)
            {
                av_free_packet(m_pPacket);
            }
        }
    }

    return frameDecoded;
}
