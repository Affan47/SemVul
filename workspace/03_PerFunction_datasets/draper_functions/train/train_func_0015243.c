escape( QString text ) const
{
    SqlStorage *storage = CollectionManager::instance()->sqlStorage();
    if( storage )
        return storage->escape( text );
    else
        return QString();
}
