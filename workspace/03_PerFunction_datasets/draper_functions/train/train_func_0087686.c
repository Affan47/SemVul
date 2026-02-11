clearVersions(QTableWidgetItem *item)
{
   if (item != m_current) {
      FileRevisions->clearContents();
      FileRevisions->setRowCount(0);
   }
   m_current = item ;
}
