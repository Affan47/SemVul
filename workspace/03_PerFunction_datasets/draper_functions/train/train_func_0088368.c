findInRectsCache(const QString &image, const QString &element, QRectF &rect) const
{
    if (!d->useCache()) {
        return false;
    }

    KConfigGroup imageGroup(d->svgElementsCache, image);
    rect = imageGroup.readEntry(element % QLatin1Literal("Size"), QRectF());

    if (rect.isValid()) {
        return true;
    }


    if (element.indexOf('_') <= 0) {
        return false;
    }

    bool invalid = false;

    QHash<QString, QSet<QString> >::iterator it = d->invalidElements.find(image);
    if (it == d->invalidElements.end()) {
        QSet<QString> elements = imageGroup.readEntry("invalidElements", QStringList()).toSet();
        d->invalidElements.insert(image, elements);
        invalid = elements.contains(element);
    } else {
        invalid = it.value().contains(element);
    }

    return invalid;
}
