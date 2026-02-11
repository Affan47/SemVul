evas_textblock_cursor_compare(const Evas_Textblock_Cursor *cur1, const Evas_Textblock_Cursor *cur2)
{
   Eina_Inlist *l1, *l2;

   if (!cur1) return 0;
   if (!cur2) return 0;
   if (cur1->obj != cur2->obj) return 0;
   if ((!cur1->node) || (!cur2->node)) return 0;
   if (cur1->node == cur2->node)
     {
	if (cur1->pos < cur2->pos) return -1;
	else if (cur1->pos > cur2->pos) return 1;
	return 0;
     }
   for (l1 = EINA_INLIST_GET(cur1->node),
        l2 = EINA_INLIST_GET(cur1->node); (l1) || (l2);)
     {
	if (l1 == EINA_INLIST_GET(cur2->node)) return 1;
	else if (l2 == EINA_INLIST_GET(cur2->node)) return -1;
	else if (!l1) return -1;
	else if (!l2) return 1;
	l1 = l1->prev;
	l2 = l2->next;
     }
   return 0;
}
