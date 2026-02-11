SqlPlaylist( const QStringList & resultRow,
                                SqlPlaylistGroupPtr parent,
                                PlaylistProvider *provider )
    : m_parent( parent )
    , m_provider( provider)
    , m_tracksLoaded( false )
{
    m_dbId = resultRow[0].toInt();
    m_name = resultRow[2];
    m_urlId = resultRow[3];
}
