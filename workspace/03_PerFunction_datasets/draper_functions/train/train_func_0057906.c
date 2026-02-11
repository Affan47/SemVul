postPopulated()
{
    if (isEmpty())
        return;

    QModelIndex parent = rootIndex();

    bool hasBookmarks = false;

    for (int i = 0; i < parent.model()->rowCount(parent); ++i) {
        QModelIndex child = parent.model()->index(i, 0, parent);

        if (child.data(BookmarksModel::TypeRole) == BookmarkNode::Bookmark) {
            hasBookmarks = true;
            break;
        }
    }

    if (!hasBookmarks)
        return;

    addSeparator();
    QAction *action = addAction(tr("Open in Tabs"));
    connect(action, SIGNAL(triggered()),
            this, SLOT(openAll()));
}
