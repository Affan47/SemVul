hasChildren( const QModelIndex &parent ) const
{
    if( !parent.isValid() )
        return true;

    GpodderTreeItem *treeItem = static_cast<GpodderTreeItem *>( parent.internalPointer() );

    if( treeItem == 0 )
        return false;

    if( treeItem->childCount() > 0 )
        return true;

    if( !qobject_cast<GpodderPodcastTreeItem *>( treeItem ) )
    {
        return true;
    }
    else
    {
        return false;
    }
}
