qmonShareTreeFindNextNode(Widget w, XtPointer cld, XtPointer cad)
{
   Widget tree = (Widget)cld;
   static int count = 0;
   ListTreeItem *current;
   int first = 0;

   DENTER(GUI_LAYER, "qmonShareTreeFindNode");

   if (!matches && strcmp(search_for, "")) {
      first = 1;
      count = 0;
      matches = ListTreeBuildSearchList(tree, ListTreeFirstItem(tree),search_for, 1);


   }


   if (matches && matches->count > 1 && count < matches->count) {
      if (first) {
         first = 0;
         count++;
      }
      current = matches->items[count];
      DPRINTF(("current->text: %s, current->count = %d\n", current->text, current->count));


      ListTreeOpenNode(tree, current);
      ListTreeMakeItemVisible(tree, current);
      ListTreeHighlightItem(tree, current, True);

      count++;
      if (count == matches->count)
         count = 0;
   }

   DEXIT;
}
