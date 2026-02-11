rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        return m_bookmarksManager->bookmarks()->children().count();

    const BookmarkNode *item = static_cast<BookmarkNode*>(parent.internalPointer());
    return item->children().count();
}
