addBookmark(BookmarkNode *parent, BookmarkNode *node, int row)
{
    if (!m_loaded)
        return;
    Q_ASSERT(parent);
    InsertBookmarksCommand *command = new InsertBookmarksCommand(this, parent, node, row);
    m_commands.push(command);
}
