evas_textblock_cursor_range_formats_get(const Evas_Textblock_Cursor *cur1, const Evas_Textblock_Cursor *cur2)
{
   Evas_Object *obj;
   Eina_List *ret = NULL;
   Evas_Object_Textblock_Node_Text *n1, *n2;
   Evas_Object_Textblock_Node_Format *first, *last;
   if (!cur1 || !cur1->node) return NULL;
   if (!cur2 || !cur2->node) return NULL;
   if (cur1->obj != cur2->obj) return NULL;

   obj = cur1->obj;
   TB_HEAD_RETURN(NULL);

   if (evas_textblock_cursor_compare(cur1, cur2) > 0)
     {
        const Evas_Textblock_Cursor *tc;

        tc = cur1;
        cur1 = cur2;
        cur2 = tc;
     }
   n1 = cur1->node;
   n2 = cur2->node;


   last = n2->format_node;


   if (!last)
      return NULL;


   if (last->text_node == n2)
     {
        Evas_Object_Textblock_Node_Format *fnode = last;
        while (fnode && (fnode->text_node == n2))
          {
             last = fnode;
             fnode = _NODE_FORMAT(EINA_INLIST_GET(fnode)->next);
          }
     }


   first = n1->format_node;
   if ((first->text_node == n1) || (first != last))
     {
        Evas_Object_Textblock_Node_Format *fnode = first;

        if (first->text_node != n1)
          {
             first = _NODE_FORMAT(EINA_INLIST_GET(first)->next);
          }

        while (fnode)
          {
             ret = eina_list_append(ret, fnode);
             if (fnode == last)
                break;
             fnode = _NODE_FORMAT(EINA_INLIST_GET(fnode)->next);
          }
     }

   return ret;

}
