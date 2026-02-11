playChildTracks( CollectionTreeItem *item, Playlist::AddOptions insertMode )
{
    QSet<CollectionTreeItem*> items;
    items.insert( item );

    playChildTracks( items, insertMode );
}
