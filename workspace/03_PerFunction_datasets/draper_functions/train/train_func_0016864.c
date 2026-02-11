SlotContextMenu (const QPoint &Position)
{
   QMenu        Menu;
   QAction      ActionNewDir (tr("New directory"), this);
   QAction      ActionRmDir  (tr("Remove directory"), this);
   QAction    *pAction;
   QModelIndex  CurrentIndex;

   CurrentIndex = pOwn->pTree->indexAt (Position);
   if (CurrentIndex.isValid() && pOwn->pModel->isDir (CurrentIndex))
   {
      Menu.addAction (&ActionNewDir);
      Menu.addAction (&ActionRmDir);

      pAction = Menu.exec (pOwn->pTree->mapToGlobal (Position));

      if (pAction == &ActionNewDir)
      {
         pOwn->pModel->mkdir (CurrentIndex, tr("NewDirectory", "Name of the new directory that will be created"));
      }
      else if (pAction == &ActionRmDir)
      {
         bool Success = pOwn->pModel->rmdir (CurrentIndex);
         if (!Success)
            CHK_EXIT (t_DlgMessage::Show ("Cannot be removed", "Only empty directories can be removed", false))
      }
   }
}
