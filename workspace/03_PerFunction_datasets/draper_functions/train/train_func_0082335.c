fileMetaInfo( const KFileItemList& items)
{
    return new MetaInfoJob(items);
}
