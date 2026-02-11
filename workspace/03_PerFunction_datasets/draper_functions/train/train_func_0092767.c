capturedShortcut(const QVariant &newShortcut, const QModelIndex &index)
{

    if (!index.isValid())
        return;
    int column = index.column();
    KShortcutsEditorItem *item = itemFromIndex(ui.list, index);
    Q_ASSERT(item);

    if (column >= LocalPrimary && column <= GlobalAlternate)
        changeKeyShortcut(item, column, newShortcut.value<QKeySequence>());
    else if (column == ShapeGesture)
        changeShapeGesture(item, newShortcut.value<KShapeGesture>());
    else if (column == RockerGesture)
        changeRockerGesture(item, newShortcut.value<KRockerGesture>());
}
