closestItem(const KUrl &url) const
{
    int foundRow = -1;
    int maxLength = 0;


    for (int row = 0; row<d->items.size(); ++row) {
        KFilePlacesItem *item = d->items[row];
        KUrl itemUrl = KUrl(item->data(UrlRole).toUrl());

        if (itemUrl.isParentOf(url)) {
            const int length = itemUrl.prettyUrl().length();
            if (length > maxLength) {
                foundRow = row;
                maxLength = length;
            }
        }
    }

    if (foundRow==-1)
        return QModelIndex();
    else
        return createIndex(foundRow, 0, d->items[foundRow]);
}
