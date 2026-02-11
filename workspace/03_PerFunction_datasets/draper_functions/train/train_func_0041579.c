editName()
{
    QModelIndex idx = tree->currentIndex();
    idx = idx.sibling(idx.row(), 0);
    tree->edit(idx);
}
