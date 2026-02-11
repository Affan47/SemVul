renameBookmarkRecursively( BookmarkGroupPtr group, const QString& oldName, const QString& newName )
{
    foreach( AmarokUrlPtr item, group->childBookmarks() )
    {
        debug() << "item->name(): " << item->name();
        if( item->name() == oldName)
        {
            debug() << "Renaming Bookmark: " << oldName;
            item->rename(newName);
            return true;
        }
    }


    foreach( BookmarkGroupPtr childGroup, group->childGroups() )
    {
        if( renameBookmarkRecursively( childGroup, oldName, newName ) )
            return true;
    }

    return false;

}
