addEntry(Entry * entry)
{
    QString preview = entry->preview().representation();
    if (!preview.isEmpty()) {
        m_hasPreviewImages = true;
    }


    beginInsertRows(QModelIndex(), m_entries.count(), m_entries.count());
    m_entries.append(entry);
    endInsertRows();

    if (!preview.isEmpty()) {
        m_imageIndexes.insert(preview, index(m_entries.count() - 1, 0));
        QAsyncImage *pix = new QAsyncImage(preview, this);
        connect(pix, SIGNAL(signalLoaded(QString,QImage)),
                this, SLOT(slotEntryPreviewLoaded(QString,QImage)));
    }
}
