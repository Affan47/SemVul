addCategory( BrowserCategory *category )
{
    if( !category )
    {
        debug() << "Trying to add a nonexistent service to the BrowserCategoryListModel!";
        return;
    }
    beginInsertRows ( QModelIndex(), m_categories.count(), m_categories.count() );
    m_categories.push_back( category );
    endInsertRows();
}
