allSubGroups(const QByteArray& parentGroup) const
{
    QSet<QByteArray> groups;
    QByteArray theGroup = parentGroup + '\x1d';
    groups << parentGroup;

    for (KEntryMap::const_iterator entryMapIt = entryMap.begin(); entryMapIt != entryMap.end(); ++entryMapIt) {
        const KEntryKey& key = entryMapIt.key();
        if (key.mKey.isNull() && key.mGroup.startsWith(theGroup)) {
            groups << key.mGroup;
        }
    }
    return groups;
}
