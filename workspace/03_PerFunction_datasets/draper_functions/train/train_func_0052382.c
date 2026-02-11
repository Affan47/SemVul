replayGain( Meta::ReplayGainTag mode ) const
{
    switch( mode )
    {
    case Meta::ReplayGain_Track_Gain:
        return d->m_data.trackGain;
    case Meta::ReplayGain_Track_Peak:
        return d->m_data.trackPeak;
    case Meta::ReplayGain_Album_Gain:
        return d->m_data.albumGain;
    case Meta::ReplayGain_Album_Peak:
        return d->m_data.albumPeak;
    }
    return 0.0;
}
