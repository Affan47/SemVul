CountChildren(ListTreeWidget w, ListTreeItem *item, int x, int y)
#else
static int CountChildren(w, item, x, y)
ListTreeWidget w;
ListTreeItem *item;
int x;
int y;
#endif
{
   int height;

   x += (int) w->list.Indent + w->list.pixWidth;
   while (item) {
      height = CountItem(w, item, x, y);

      y += height + (int) w->list.VSpacing;
      if ((item->firstchild) && (item->open))
         y = CountChildren(w, item->firstchild, x, y);

      item = item->nextsibling;
   }
   return y;
}
