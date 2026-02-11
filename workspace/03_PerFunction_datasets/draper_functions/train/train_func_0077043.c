findEntry(const QByteArray& group, const QByteArray& key, KEntryMap::SearchFlags flags) const
{
    KEntryKey theKey(group, key, false, bool(flags&SearchDefaults));


    if (flags&SearchLocalized) {
        theKey.bLocal = true;

        ConstIterator it = find(theKey);
        if (it != constEnd())
            return it;

        theKey.bLocal = false;
    }
    return find(theKey);
}
