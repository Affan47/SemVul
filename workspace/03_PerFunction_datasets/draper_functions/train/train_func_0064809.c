index( Dynamic::BiasPtr bias ) const
{
    QModelIndex res;


    for( int i = 0; i < m_playlists.count(); i++ )
    {
        res = parent( i, qobject_cast<BiasedPlaylist*>(m_playlists[i]), bias );
        if( res.isValid() )
            break;
    }

    if( !res.isValid() )
        return res;

    QObject* o = static_cast<QObject*>(res.internalPointer());
    BiasedPlaylist* parentPlaylist = qobject_cast<BiasedPlaylist*>(o);
    AndBias* parentBias = qobject_cast<Dynamic::AndBias*>(o);


    if( parentPlaylist )
    {
        return createIndex( 0, 0, bias.data() );
    }

    else if( parentBias )
    {
        return createIndex( parentBias->biases().indexOf( bias ), 0, bias.data() );
    }
    else
    {
        return QModelIndex();
    }
}
