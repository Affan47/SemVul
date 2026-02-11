DoOnPluginKeyDown (int code)
{
   if (code != WXK_UP && code != WXK_DOWN)
         return false;

   long itemIndex = -1;
   long itemIndex2 = -1;
   itemIndex = PluginList->GetNextItem(itemIndex,
         wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
   if (itemIndex == -1)
         return false;

   if (last_selected == -1)
         return false;

   ExtImportItems *items = wxGetApp().mImporter->GetImportItems();
   ExtImportItem *item = &(*items)[last_selected];

   if (code == WXK_UP && itemIndex == 0)
      return false;
   else if (code == WXK_DOWN && itemIndex == PluginList->GetItemCount() - 1)
      return false;

   if (code == WXK_UP)
   {
      itemIndex2 = itemIndex - 1;
   }
   else if (code == WXK_DOWN)
   {
      itemIndex2 = itemIndex + 1;
   }
   SwapPluginRows (itemIndex, itemIndex2);
   if (mFakeKeyEvent)
   {
      PluginList->SetItemState (itemIndex, 0, wxLIST_STATE_SELECTED);
      PluginList->SetItemState (itemIndex2, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
   }
   int fcount = item->filter_objects.Count();
   if (item->divider >= fcount)
   {
      item->divider = -1;
   }
   if (item->divider < -1)
      item->divider = item->filter_objects.Count() - 1;

   return true;
}
