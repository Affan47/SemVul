slotMetaInfo(KIO::Job*, const QByteArray &data)
{
    Q_D(MetaInfoJob);
    KFileMetaInfo info;
    QDataStream s(data);

    s >> info;

    KFileItem item = d->items.at( d->currentItem );
    item.setMetaInfo(info);
    emit gotMetaInfo(item);
    d->succeeded = true;
}
