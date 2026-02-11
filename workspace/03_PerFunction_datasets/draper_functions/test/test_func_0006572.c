get(long id, const KUrl &url, const MetaData &metaData)
{
   Q_D(MultiGetJob);
   MultiGetJobPrivate::GetRequest entry(id, url, metaData);
   entry.metaData["request-id"] = QString::number(id);
   d->m_waitQueue.append(entry);
}
