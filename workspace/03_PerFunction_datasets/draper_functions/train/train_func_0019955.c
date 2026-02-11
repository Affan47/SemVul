operator>>(QDataStream& in, QOrganizerItem& item)
{
    quint8 formatVersion;
    in >> formatVersion;
    if (formatVersion == 1) {
        item = QOrganizerItem();
        QString itemIdString;
        QString collectionIdString;
        QList<QOrganizerItemDetail> details;
        in >> itemIdString >> collectionIdString >> details;
        item.setId(QOrganizerItemId::fromString(itemIdString));
        item.setCollectionId(QOrganizerCollectionId::fromString(collectionIdString));
        item.d->m_details = details;
    } else {
        in.setStatus(QDataStream::ReadCorruptData);
    }
    return in;
}
