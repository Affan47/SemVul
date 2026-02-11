findByName( const KDirLister *lister, const QString& _name ) const
{
    Q_ASSERT(lister);

    for (KUrl::List::const_iterator it = lister->d->lstDirs.constBegin();
         it != lister->d->lstDirs.constEnd(); ++it) {
        DirItem* dirItem = itemsInUse.value((*it).url());
        Q_ASSERT(dirItem);
        const KFileItem item = dirItem->lstItems.findByName(_name);
        if (!item.isNull())
            return item;
    }

    return KFileItem();
}
