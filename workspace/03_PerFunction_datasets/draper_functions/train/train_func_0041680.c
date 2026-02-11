group( const QString &name )
{
    DEBUG_BLOCK
    Playlists::SqlPlaylistGroupPtr group;

    if( name.isEmpty() )
        return m_root;


    m_root->clear();

    foreach( const Playlists::SqlPlaylistGroupPtr &group, m_root->allChildGroups() )
    {
        debug() << group->name();
        if( group->name() == name )
        {
            debug() << "match";
            return group;
        }
    }

    debug() << "Creating a new group " << name;
    group = new Playlists::SqlPlaylistGroup( name, m_root, this );
    group->save();

    return group;
}
