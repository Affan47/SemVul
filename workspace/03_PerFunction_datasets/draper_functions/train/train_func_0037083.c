HighlightAllVisible(ListTreeWidget w, Boolean state, Boolean draw)
#else
static void HighlightAllVisible(w, state, draw)
ListTreeWidget w;
Boolean state;
Boolean draw;
#endif
{
   ListTreeItem *item;

   item = w->list.first;
   while (item) {
      HighlightItem(w, item, state, draw);
      if (item->firstchild && item->open) {
         HighlightVisibleChildren(w, item->firstchild, state, draw);
      }
      item = item->nextsibling;
   }
}
