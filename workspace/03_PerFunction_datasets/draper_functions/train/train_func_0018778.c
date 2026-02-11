_k_activated(const QModelIndex &index)
{
    const KUrl url = urlForProxyIndex(index);
    if (url.isValid())
        emit q->activated(url);
}
