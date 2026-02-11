showInfoForJob(QTableWidgetItem * )
{
   QTreeWidgetItem* pageSelectorTreeWidgetItem = mainWin->getFromHash(this);
   new Job(m_currentJob, pageSelectorTreeWidgetItem);
}
