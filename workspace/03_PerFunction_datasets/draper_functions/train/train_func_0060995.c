setBookmarkArgRecursively(  BookmarkGroupPtr group, const QString& name, const QString& key, const QString &value )
{
    foreach( AmarokUrlPtr item, group->childBookmarks() )
    {
        if( item->name() == name )
        {
            item->setArg( key, value );
            item->saveToDb();
            return true;
        }
    }


    foreach( BookmarkGroupPtr childGroup, group->childGroups() )
    {
        if( setBookmarkArgRecursively( childGroup, name, key, value ) )
            return true;
    }

    return false;

}
