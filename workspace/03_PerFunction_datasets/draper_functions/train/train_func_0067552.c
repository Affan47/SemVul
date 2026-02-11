ListTreeOpenLikeTree(Widget w, ListTreeItem *new, ListTreeItem *old)
#else
void ListTreeOpenLikeTree(w, new, old)
Widget w;
ListTreeItem *new;
ListTreeItem *old;
#endif
{
   ListTreeItem *new_to_set;

   TreeCheck(lw, "in ListTreeOpenLikeTree");

   while (old) {
      new_to_set = ListTreeFindSiblingName(w, new, old->text);
      if (new_to_set) {
         new_to_set->open = old->open;
         if (old->firstchild && new_to_set->firstchild)
            ListTreeOpenLikeTree(w, new_to_set->firstchild, old->firstchild);
      }

      old = old->nextsibling;
   }
}
