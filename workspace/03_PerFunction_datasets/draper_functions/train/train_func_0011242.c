updateBackground(unsigned long oldbg_)
{
  V v=(model()!=0)?((AplusModel*)model())->aplusVar():0;
  A a=(model()!=0)?((AplusModel*)model())->a():0;
  if (v!=0)
   {
     AColorFunction *bgFunc=AplusModel::getBgFunc(v);
     unsigned long bg=(bgFunc!=0)?bgFunc->invoke(v,a):background();
     if (bg!=oldbg_)  MSTreeView<AplusTreeItem>::updateBackground(oldbg_);
   }
}
