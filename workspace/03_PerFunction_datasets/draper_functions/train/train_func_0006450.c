restoreCurrentItem()
{
  Q_Q(KViewStateSaver);

  QModelIndex currentIndex = q->indexFromConfigString(m_selectionModel->model(), m_pendingCurrent);
  if ( currentIndex.isValid() )
  {
    if (m_treeView)
      m_treeView->setCurrentIndex(currentIndex);
    else
      m_selectionModel->setCurrentIndex(currentIndex, QItemSelectionModel::NoUpdate);
    m_pendingCurrent.clear();
  }
}
