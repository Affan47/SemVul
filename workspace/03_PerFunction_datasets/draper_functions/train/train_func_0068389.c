mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData;
    QList<QUrl> urls;
    foreach (const QModelIndex &idx, indexes) {
        QUrl url = idx.data(HistoryModel::UrlRole).toUrl();
        urls.append(url);
    }
    mimeData->setUrls(urls);
    return mimeData;
}
