slotAccessibilityChanged( bool accessible, const QString &udi )
{
    debug() << "accessibility of device " << udi << " has changed to accessible = " << (accessible ? "true":"false");
    if( accessible )
    {
        Solid::Device device( udi );
        m_type[udi] = MediaDeviceCache::SolidVolumeType;
        Solid::StorageAccess *ssa = device.as<Solid::StorageAccess>();
        if( ssa )
            m_name[udi] = ssa->filePath();
        emit deviceAdded( udi );
        return;
    }
    else
    {
        if( m_type.contains( udi ) )
        {
            m_type.remove( udi );
            m_name.remove( udi );
            emit deviceRemoved( udi );
            return;
        }
        debug() << "Got accessibility changed to false but was not there in the first place...";
    }

    emit accessibilityChanged( accessible, udi );
}
