SqlPlaylistGroup( const QStringList & dbResultRow,
                                          SqlPlaylistGroupPtr parent,
                                          PlaylistProvider *provider )
    : m_hasFetchedChildGroups( false )
    , m_hasFetchedChildPlaylists( false )
    , m_parent( parent )
    , m_provider( provider )
{
    m_dbId = dbResultRow[0].toInt();
    m_name = dbResultRow[2];
    m_description = dbResultRow[3];
}
