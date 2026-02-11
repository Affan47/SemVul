storableData() const
{
    if (m_List) {
        QItemSelectionModel *selModel = m_List->m_List->selectionModel();

        if (!selModel->hasSelection())
            return QVariant();

        QStringList selected;
        const QStringList &uuids = m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Uuid);
        foreach(const QModelIndex &idx, selModel->selectedIndexes()) {
            selected.append(uuids.at(idx.row()));
        }
        qSort(selected);
        return selected.join("`@`");
    } else if (m_EditableList) {
        return m_EditableList->m_StringListView->getStringList().toStringList().join("`@`");
    }
    return QVariant();
}
