tellIdentified( const QString &udi )
{
    DEBUG_BLOCK
    emit identified( deviceInfo( udi ) );
}
