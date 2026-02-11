createCapabilityInterface( Capabilities::Capability::Type type )
{
    switch( type )
    {
        case Capabilities::Capability::Actions:
        {
            QList< QAction * > actions;
            actions << new BookmarkCurrentTrackPositionAction( 0 );
            return new Capabilities::ActionsCapability( actions );
        }
        case Capabilities::Capability::WriteTimecode:
            return new TimecodeWriteCapabilityPodcastImpl( this );
        case Capabilities::Capability::LoadTimecode:
            return new TimecodeLoadCapabilityPodcastImpl( this );
        default:
            return 0;
    }
}
