_k_sourceLayoutAboutToBeChanged()
{


    Q_Q(KIdentityProxyModel);

    q->layoutAboutToBeChanged();

    Q_FOREACH(const QModelIndex &proxyPersistentIndex, q->persistentIndexList()) {
        Q_ASSERT(proxyPersistentIndex.isValid());
        const QPersistentModelIndex srcPersistentIndex = q->mapToSource(proxyPersistentIndex);
        if (!srcPersistentIndex.isValid())
            continue;
        proxyIndexes << proxyPersistentIndex;
        layoutChangePersistentIndexes << srcPersistentIndex;
    }
}
