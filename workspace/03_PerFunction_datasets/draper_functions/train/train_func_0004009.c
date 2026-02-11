qmonShareTreeMenu(Widget w, XtPointer cld, XtPointer cad)
{
   ListTreeWidget tree = (ListTreeWidget) cld;
   ListTreeItemReturnStruct *ret = (ListTreeItemReturnStruct *)cad;
   Boolean status;
   char name[256];
   Cardinal share;

   DENTER(GUI_LAYER, "qmonShareTreeMenu");


   if (ret->item && ret->item->text && !strcasecmp(ret->item->text, "Root")) {
      DEXIT;
      return;
   }


   if (ret->item->parent && ret->item->parent->text && !strcasecmp(ret->item->parent->text, "default")) {
      DEXIT;
      return;
   }

   if (rmon_mlgetl(&RMON_DEBUG_ON, GUI_LAYER) & INFOPRINT) {
      printf ("MENU: item=%s\n", ret->item->text);
   }


   strcpy(name, ret->item->text);
   share = ((tSTNUserData*)ret->item->user_data)->share;
   status = AskForNode(w, name, 256, &share);

   if (status) {
      node_data(ret->item, share, NULL);
      ListTreeRenameItem((Widget)tree, ret->item, name);


      ListTreeHighlightItem((Widget)tree, ret->item, True);
      dirty = True;
   }


   DEXIT;
}
