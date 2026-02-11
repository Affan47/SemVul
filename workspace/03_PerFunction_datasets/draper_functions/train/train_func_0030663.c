slotEntryChanged(Entry * entry)
{
    int i = m_entries.indexOf(entry);
    QModelIndex entryIndex = index(i, 0);
    emit dataChanged(entryIndex, entryIndex);
}
