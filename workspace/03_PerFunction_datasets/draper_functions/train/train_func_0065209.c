currentItemIsTemplate() const
{
    QModelIndex index = d->m_ui->categoryTreeView->selectionModel()->currentIndex();
    if (index.isValid()) {
        return d->m_Model->isTemplate(index);
    }
    return false;
}
