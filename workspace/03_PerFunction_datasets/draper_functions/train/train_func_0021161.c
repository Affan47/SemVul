qmonShareTreeDeleteNode(Widget w, XtPointer cld, XtPointer cad)
{
   Widget tree = (Widget) cld;
   ListTreeItem *item = NULL;
   ListTreeMultiReturnStruct ret;

   DENTER(GUI_LAYER, "qmonShareTreeDeleteNode");

   ListTreeGetHighlighted(tree, &ret);
   if (ret.count == 1)
      item = ret.items[0];

   if (!item) {
      DEXIT;
      return;
   }


   if (item->parent && item->parent->text && !strcasecmp(item->parent->text, "default")) {
      DEXIT;
      return;
   }

   ListTreeDelete(tree, item);
   dirty = True;

   DEXIT;
}
