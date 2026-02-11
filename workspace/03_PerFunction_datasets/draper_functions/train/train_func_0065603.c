closePage(int item)
{
   QTreeWidgetItem *currentitem;
   Pages *page = NULL;

   if (item >= 0) {
     page = (Pages *)tabWidget->widget(item);
   } else {
      currentitem = treeWidget->currentItem();

      if (getFromHash(currentitem)) {
         page = getFromHash(currentitem);
      }
   }

   if (page) {
      if (page->isCloseable()) {
         page->closeStackPage();
      } else {
         page->hidePage();
      }
   }
}
