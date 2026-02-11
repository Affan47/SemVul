updateSorting(QDir::SortFlags sort)
{
    kDebug(kfile_area) << "changing sort flags from"  << sorting << "to" << sort;
    if (sort == sorting) {
        return;
    }

    if ((sorting ^ sort) & QDir::DirsFirst) {


        Qt::SortOrder tmpSortOrder = (sortOrder() == Qt::AscendingOrder ? Qt::DescendingOrder : Qt::AscendingOrder);
        proxyModel->sort(sortOrder(), tmpSortOrder);
        proxyModel->setSortFoldersFirst(sort & QDir::DirsFirst);
    }

    sorting = sort;
    parent->updateSortActions();
    proxyModel->sort(sortColumn(), sortOrder());


    QTreeView* treeView = qobject_cast<QTreeView*>(itemView);
    if (treeView != 0) {
        QHeaderView* headerView = treeView->header();
        headerView->blockSignals(true);
        headerView->setSortIndicator(sortColumn(), sortOrder());
        headerView->blockSignals(false);
    }

    _k_assureVisibleSelection();
}
