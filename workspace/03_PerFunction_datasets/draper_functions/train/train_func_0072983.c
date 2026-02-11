registerCollection(ActionCollection* collection)
{
    Q_ASSERT(collection);
    const QString name = collection->objectName();

    if (!d->collections.contains(name))
    {
        d->collections.insert(name, collection);
        d->collectionnames.append(name);
    }
    connectSignals(collection, true);
    emitUpdated();
}
