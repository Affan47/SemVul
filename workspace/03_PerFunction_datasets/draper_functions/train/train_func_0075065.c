leaveEvent(QEvent *event)
{
    QListView::leaveEvent(event);
    if (d->hoveredIndex.isValid()) {
        viewport()->update(visualRect(d->hoveredIndex));
        d->hoveredIndex = QModelIndex();
    }
    if (d->categoryDrawerV3 && d->hoveredBlock->height != -1) {
        const QModelIndex categoryIndex = d->proxyModel->index(d->hoveredBlock->firstIndex.row(), d->proxyModel->sortColumn(), rootIndex());
        const QStyleOptionViewItemV4 option = d->blockRect(categoryIndex);
        d->categoryDrawerV3->mouseLeft(categoryIndex, option.rect);
        *d->hoveredBlock = Private::Block();
        d->hoveredCategory = QString();
        viewport()->update(option.rect);
    }
}
