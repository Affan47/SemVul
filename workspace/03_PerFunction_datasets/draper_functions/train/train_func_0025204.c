getInfo(AlbumPtr album)
{
    DEBUG_BLOCK
    ScriptableServiceAlbum * serviceAlbum = dynamic_cast< ScriptableServiceAlbum * >( album.data() );
    if (serviceAlbum == 0) return;

    emit( info( serviceAlbum->description() ) );

    if ( serviceAlbum->description().isEmpty() )
    {
        showLoading( i18n( "Loading info..." ) );
        ScriptManager::instance()->ServiceScriptRequestInfo( m_serviceName, serviceAlbum->level(), serviceAlbum->callbackString() );
    }
}
