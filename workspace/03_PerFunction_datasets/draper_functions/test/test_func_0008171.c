selectionChanged()
{
    QModelIndexList selection = m_ui.listView->selectionModel()->selectedIndexes();
    if ( selection.count() == 1 ) {
        QString name = m_ui.listView->model()->data( selection[ 0 ] ).toString();

        m_keepSelection = true;
        m_ui.editName->setText( name );
        m_keepSelection = false;
    }
}
