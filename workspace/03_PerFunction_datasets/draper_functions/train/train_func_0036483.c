showInfoVolume(QListWidgetItem *item)
{
   QString s= item->text();
   QTreeWidgetItem* pageSelectorTreeWidgetItem = mainWin->getFromHash(this);

   MediaInfo *m = new MediaInfo(pageSelectorTreeWidgetItem, s);
   connect(m, SIGNAL(destroyed()), this, SLOT(populateTree()));
}
