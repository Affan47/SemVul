createCapabilityInterface(Capabilities::Capability::Type type)
{
    switch( type )
    {
        case Capabilities::Capability::MultiSource:
            return new Capabilities::MultiSourceCapabilityImpl( this );
        default:
            return 0;
    }
}
