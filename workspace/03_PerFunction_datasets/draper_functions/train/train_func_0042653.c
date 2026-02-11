TreeToCull(
Widget tree,
ListTreeItem *item
) {
   lList *lp = NULL;
   lListElem *ep = NULL;
   ListTreeItem *node = NULL;
   tSTNUserData *data;

   DENTER(GUI_LAYER, "TreeToCull");

   if (!item)
      node = ListTreeFirstItem(tree);
   else
      node = ListTreeFirstChild(item);

   while (node) {
      data = (tSTNUserData*)node->user_data;
      if (!data->temp) {
         ep = lAddElemStr(&lp, STN_name, node->text, STN_Type);
         lSetUlong(ep, STN_shares, data->share);


         if (ListTreeFirstChild(node))
            lSetList(ep, STN_children, TreeToCull(tree, node));
      }

      node = ListTreeNextSibling(node);
   }

   DEXIT;
   return lp;
}
