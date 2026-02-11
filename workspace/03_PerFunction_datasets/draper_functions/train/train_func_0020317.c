canMoveDown() const
{
    if (!m_CurrentView)
        return false;
    QModelIndex idx = m_CurrentView->prescriptionListView()->currentIndex();
    if (!idx.isValid())
        return false;
    if (idx.row() < (m_CurrentView->prescriptionListView()->model()->rowCount()-1))
        return true;
    return false;
}
