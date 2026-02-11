listCachedRectKeys(const QString &image) const
{
    if (!d->useCache()) {
        return QStringList();
    }

    KConfigGroup imageGroup(d->svgElementsCache, image);
    QStringList keys = imageGroup.keyList();

    QMutableListIterator<QString> i(keys);
    while (i.hasNext()) {
        QString key = i.next();
        if (key.endsWith("Size")) {

            key.resize(key.size() - 4);
            i.setValue(key);
        } else {
            i.remove();
        }
    }
    return keys;
}
