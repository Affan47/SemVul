slotPropertyModified(int , const QList<ChangeDescription> &changes)
{
    QMap<QString,int> result;

    foreach (const ChangeDescription &change, changes) {
        QString key = change.key;
        bool added = change.added;
        bool removed = change.removed;

        Solid::GenericInterface::PropertyChange type = Solid::GenericInterface::PropertyModified;

        if (added) {
            type = Solid::GenericInterface::PropertyAdded;
        } else if (removed) {
            type = Solid::GenericInterface::PropertyRemoved;
        }

        result[key] = type;
        d->cache.remove(key);

        if (d->cache.isEmpty()) {
            d->cacheSynced = false;
            d->invalidKeys.clear();
        } else {
            d->invalidKeys.insert(key);
        }
    }


    emit propertyChanged(result);
}
