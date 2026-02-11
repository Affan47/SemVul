retrieve(float *const *output, size_t samples) const
{
    Profiler profiler("RubberBandStretcher::Impl::retrieve");

    size_t got = samples;

    for (size_t c = 0; c < m_channels; ++c) {
        size_t gotHere = m_channelData[c]->outbuf->read(output[c], got);
        if (gotHere < got) {
            if (c > 0) {
                if (m_debugLevel > 0) {
                    cerr << "RubberBandStretcher::Impl::retrieve: WARNING: channel imbalance detected" << endl;
                }
            }
            got = gotHere;
        }
    }

    return got;
}
