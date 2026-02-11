HighlightItem(ListTreeWidget w, ListTreeItem * item,
                           Boolean state, Boolean draw)
#else
static void HighlightItem(w, item, state, draw)
ListTreeWidget w;
ListTreeItem * item;
Boolean state;
Boolean draw;
#endif
{
   if (item) {
      if (item == w->list.highlighted && !state) {
         w->list.highlighted = NULL;
         if (draw && item->count>=w->list.topItemPos)
            DrawItemHighlightClear(w, item);
      }
      else if (state != item->highlighted) {


         item->highlighted = state;
         if (draw && item->count>=w->list.topItemPos &&
               item->count<=w->list.bottomItemPos)
            DrawItemHighlightClear(w, item);

      }
   }
}
