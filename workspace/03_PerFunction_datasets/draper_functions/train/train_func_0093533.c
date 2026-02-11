keyListImpl(const QByteArray& theGroup) const
{
    QStringList keys;

    const KEntryMapConstIterator theEnd = entryMap.constEnd();
    KEntryMapConstIterator it = entryMap.findEntry(theGroup);
    if (it != theEnd) {
        ++it;

        QSet<QString> tmp;
        for (; it != theEnd && it.key().mGroup == theGroup; ++it) {
            const KEntryKey& key = it.key();
            if (key.mGroup == theGroup && !key.mKey.isNull() && !it->bDeleted)
                tmp << QString::fromUtf8(key.mKey);
        }
        keys = tmp.toList();
    }

    return keys;
}
