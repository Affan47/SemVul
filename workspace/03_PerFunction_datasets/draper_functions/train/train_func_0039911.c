createCapabilityInterface( Capabilities::Capability::Type type )
{
    DEBUG_BLOCK

    if ( type == Capabilities::Capability::BoundedPlayback )
        return new Capabilities::TimecodeBoundedPlaybackCapability( this );
    else
        return 0;
}
