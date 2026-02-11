emptyBookmarkGroup(KBookmarkGroup & root)
{
    KBookmark bookmark = root.first();
    while (!bookmark.isNull()) {
        KBookmark bookmarkToRemove = bookmark;
        bookmark = root.next(bookmark);
        root.deleteBookmark(bookmarkToRemove);
    }
}
