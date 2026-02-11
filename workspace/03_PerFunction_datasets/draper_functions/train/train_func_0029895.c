pgInitialize(const QString &tname, QTreeWidgetItem *parentTreeWidgetItem)
{
   m_docked = false;
   m_onceDocked = false;
   if (tname.size()) {
      m_name = tname;
   }
   m_parent = mainWin->tabWidget;
   m_console = mainWin->currentConsole();

   if (!parentTreeWidgetItem) {
      parentTreeWidgetItem = m_console->directorTreeItem();
   }

   QTreeWidgetItem *item = new QTreeWidgetItem(parentTreeWidgetItem);
   QString name;
   treeWidgetName(name);
   item->setText(0, name);
   mainWin->hashInsert(item, this);
   setTitle();
}
