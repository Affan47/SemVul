writeExpandedSettings()
{
   QSettings settings(m_console->m_dir->name(), "bat");
   settings.beginGroup("StorageTreeExpanded");
   int childcount = m_topItem->childCount();
   for (int cnt=0; cnt<childcount; cnt++) {
      QTreeWidgetItem *item = m_topItem->child(cnt);
      settings.setValue(item->text(0), item->isExpanded());
   }
   settings.endGroup();
}
