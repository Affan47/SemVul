_k_assureVisibleSelection()
{
    if (itemView == 0) {
        return;
    }

    QItemSelectionModel* selModel = itemView->selectionModel();
    if (selModel->hasSelection()) {
        const QModelIndex index = selModel->currentIndex();
        itemView->scrollTo(index, QAbstractItemView::EnsureVisible);
        _k_triggerPreview(index);
    }
}
