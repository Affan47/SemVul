treeItemClicked(QTreeWidgetItem *item, int )
{

   Pages* page = getFromHash(item);
   if (page) {
      int stackindex = tabWidget->indexOf(page);

      if (stackindex >= 0) {
         tabWidget->setCurrentWidget(page);
      }
      page->dockPage();

      page->PgSeltreeWidgetClicked();
   } else {
      Dmsg0(000, "Page not in hash");
   }
}
