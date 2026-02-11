selectEvent(const QString& event)
{
    eventSelected(event);
    if(!event.isEmpty())
    {
        const QStringList& list = m_filterModel->stringList();
        int row = list.indexOf(event);
        if(row >= 0)
        {
            QModelIndex index = m_filterModel->index(row, 0);
            if(index.isValid())
            {
                ui->tagList->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
                ui->tagList->scrollTo(index);
            }
        }
    }
}
