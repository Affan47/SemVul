calculate_share(
ListTreeItem *item
) {
   ListTreeItem *parent;
   ListTreeItem *sibling;
   double level_sum = 0.0;
   double share;

   DENTER(GUI_LAYER, "calculate_share");

   if (!item) {
      DEXIT;
      return 1.0;
   }

   parent = ListTreeParent(item);


   share = calculate_share(parent);

   if (parent) {
      sibling = ListTreeFirstChild(parent);
      while (sibling) {


         level_sum += node_share(sibling->user_data);

         sibling = ListTreeNextSibling(sibling);
      }

      if (level_sum > 0.0)
         share *= node_share(item->user_data)/level_sum;
      else
         share = 0.0;
   }


   DEXIT;

   return share;
}
