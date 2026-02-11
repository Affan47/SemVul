property(const QString &name)
{
    KConfigSkeletonItem *item = KConfigSkeleton::findItem(name);

    if (item) {
        return item->property();
    }

    return QVariant();
}
