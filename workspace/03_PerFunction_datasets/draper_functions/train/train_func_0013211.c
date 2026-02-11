invalidateAllInstances()
{
    QHash<int, CachedFontInstance*>::const_iterator i;
    QHash<int, CachedFontInstance*>::const_iterator end = instances.constEnd();
    for (i = instances.constBegin(); i != end; ++i) {
        i.value()->invalidate();
    }
}
