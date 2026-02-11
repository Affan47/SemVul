directoryItemExpanded(QTreeWidgetItem *item)
{
   int childCount = item->childCount();
   for (int i=0; i<childCount; i++) {
      QTreeWidgetItem *child = item->child(i);
      if (child->icon(0).isNull())
         child->setIcon(0, QIcon(QString::fromUtf8(":images/folder.png")));
   }
}
