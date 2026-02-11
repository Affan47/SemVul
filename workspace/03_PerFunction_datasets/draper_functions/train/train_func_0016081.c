InsertChildren(ListTreeWidget w, ListTreeItem *parent,
                              ListTreeItem *item)
#else
static void InsertChildren(w, parent, item)
ListTreeWidget w;
ListTreeItem *parent;
ListTreeItem *item;
#endif
{
   ListTreeItem *next, *newnext;


   next = item->nextsibling;


   InsertChild(w, parent, item);


   newnext = item->nextsibling;


   item->nextsibling = next;


   while (item->nextsibling) {
      item->parent = parent;
      item = item->nextsibling;
   }


   item->nextsibling = newnext;
   if (newnext)
      newnext->prevsibling = item;

}
