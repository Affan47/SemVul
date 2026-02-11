UpdateStats()
{

    _sentPacketsPerSecond = 0;
    int sentBytesPerSecond = 0;
    for (PacketQueue::iterator it = _sentQueue.begin(); it != _sentQueue.end(); ++it)
    {
        sentBytesPerSecond += it->size + 8;
        ++_sentPacketsPerSecond;
    }

    sentBytesPerSecond /= 1.f;
    _sentBandwidth = sentBytesPerSecond * (8 / 1000.0f);
}
