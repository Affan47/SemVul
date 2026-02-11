setContextMenuDockText()
{
   QTreeWidgetItem *item = mainWin->getFromHash(this);
   QString docktext;
   if (isDocked()) {
      docktext = tr("UnDock %1 Window").arg(item->text(0));
   } else {
      docktext = tr("ReDock %1 Window").arg(item->text(0));
   }

   mainWin->actionToggleDock->setText(docktext);
   setTreeWidgetItemDockColor();
}
