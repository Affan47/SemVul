parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    BookmarkNode *itemNode = node(index);
    BookmarkNode *parentNode = (itemNode ? itemNode->parent() : 0);
    if (!parentNode || parentNode == m_bookmarksManager->bookmarks())
        return QModelIndex();


    BookmarkNode *grandParentNode = parentNode->parent();
    int parentRow = grandParentNode->children().indexOf(parentNode);
    Q_ASSERT(parentRow >= 0);
    return createIndex(parentRow, 0, parentNode);
}
