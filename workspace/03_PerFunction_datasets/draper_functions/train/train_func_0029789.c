slotLoad()
{
    DEBUG_BLOCK
    foreach( BookmarkViewItemPtr item, selectedItems() )
    {
        if( typeid( * item ) == typeid( AmarokUrl ) )
        {
            AmarokUrlPtr bookmark = AmarokUrlPtr::staticCast( item );
            bookmark->run();
        }
    }
}
