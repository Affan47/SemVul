volumeMountPoint( const QString &udi ) const
{
    DEBUG_BLOCK
    Solid::Device device( udi );
    Solid::StorageAccess* ssa = device.as<Solid::StorageAccess>();
    if( !ssa || !ssa->isAccessible() )
    {
        debug() << "Not able to convert to StorageAccess or not accessible, returning empty";
        return QString();
    }
    return ssa->filePath();
}
