itemsDeleted(const QList<KDirLister *>& listers, const KFileItemList& deletedItems)
{
    Q_FOREACH(KDirLister *kdl, listers) {
        kdl->d->emitItemsDeleted(deletedItems);
    }

    Q_FOREACH(const KFileItem& item, deletedItems) {
        if (item.isDir())
            deleteDir(item.url());
    }
}
