dbClose()
{
    Q_ASSERT(m_cell.isValid());
    QString ts = m_filterModel->data(m_filterModel->index(m_cell.row(), DBLV_PATH)).toString();
    emit requestCloseDatabase(ts);
}
