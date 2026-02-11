directoryIconStateInsert(QString &fullPath, Qt::CheckState excpState)
{
   QStringList paths;
   fullPathtoSubPaths(paths, fullPath);

   if (excpState == Qt::Checked) {
      bool foundAsUnChecked = false;
      QTreeWidgetItem *firstItem = m_dirPaths.value(paths[0]);
      if (firstItem) {
         if (firstItem->checkState(0) == Qt::Unchecked)
            foundAsUnChecked = true;
      }
      if (foundAsUnChecked) {

         bool done = false;
         QListIterator<QString> siter(paths);
         while (siter.hasNext() && !done) {
            QString path = siter.next();
            QTreeWidgetItem *item = m_dirPaths.value(path);
            if (item) {
               if (item->checkState(0) != Qt::Unchecked)
                  done = true;
               else {
                  directorySetIcon(1, FolderGreenChecked, path, item);
                  if (mainWin->m_rtIconStateDebug) Pmsg1(000, "In restoreTree::directoryIconStateInsert inserting %s\n", path.toUtf8().data());
               }
            }
         }
      } else {

         if (mainWin->m_rtIconStateDebug) Pmsg1(000, "In restoreTree::directoryIconStateInsert Aqua %s\n", paths[0].toUtf8().data());
         bool done = false;
         QListIterator<QString> siter(paths);
         while (siter.hasNext() && !done) {
            QString path = siter.next();
            QTreeWidgetItem *item = m_dirPaths.value(path);
            if (item) {
               if (item->checkState(0) == Qt::Checked)
                  done = true;
               directorySetIcon(1, FolderGreenChecked, path, item);
               if (mainWin->m_rtIconStateDebug) Pmsg1(000, "In restoreTree::directoryIconStateInsert boogie %s\n", path.toUtf8().data());
            }
         }
      }
   }

   if (excpState == Qt::Unchecked) {
      bool done = false;
      QListIterator<QString> siter(paths);
      while (siter.hasNext() && !done) {
         QString path = siter.next();
         QTreeWidgetItem *item = m_dirPaths.value(path);
         if (item) {
            if (item->checkState(0) == Qt::Checked)
               done = true;
            directorySetIcon(1, FolderWhiteChecked, path, item);
            if (mainWin->m_rtIconStateDebug) Pmsg1(000, "In restoreTree::directoryIconStateInsert boogie %s\n", path.toUtf8().data());
         }
      }
   }
}
