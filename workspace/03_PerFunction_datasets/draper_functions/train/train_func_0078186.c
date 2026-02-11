getBasicMediaDeviceTrackInfo( const Meta::MediaDeviceTrackPtr &srcTrack, Meta::MediaDeviceTrackPtr destTrack )
{

    destTrack->setTitle( m_rc->libGetTitle( srcTrack ) );
    destTrack->setLength( m_rc->libGetLength( srcTrack ) );
    destTrack->setTrackNumber( m_rc->libGetTrackNumber( srcTrack ) );
    destTrack->setComment( m_rc->libGetComment( srcTrack ) );
    destTrack->setDiscNumber( m_rc->libGetDiscNumber( srcTrack ) );
    destTrack->setBitrate( m_rc->libGetBitrate( srcTrack ) );
    destTrack->setSamplerate( m_rc->libGetSamplerate( srcTrack ) );
    destTrack->setBpm( m_rc->libGetBpm( srcTrack ) );
    destTrack->setFileSize( m_rc->libGetFileSize( srcTrack ) );
    destTrack->setPlayCount( m_rc->libGetPlayCount( srcTrack ) );
    destTrack->setLastPlayed( m_rc->libGetLastPlayed( srcTrack ) );
    destTrack->setRating( m_rc->libGetRating( srcTrack ) );
    destTrack->setReplayGain( m_rc->libGetReplayGain( srcTrack ) );

    destTrack->setPlayableUrl( m_rc->libGetPlayableUrl( srcTrack ) );

    destTrack->setType( m_rc->libGetType( srcTrack ) );
}
