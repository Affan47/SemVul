closeStackPage()
{

   QTreeWidgetItem *item=mainWin->getFromHash(this);

   if (item) {
      mainWin->hashRemove(item, this);

      delete item;
   }

   delete this;
}
