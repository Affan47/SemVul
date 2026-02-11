evas_textblock_cursor_range_geometry_get(const Evas_Textblock_Cursor *cur1, const Evas_Textblock_Cursor *cur2)
{
   Evas_Object_Textblock *o;
   Evas_Object_Textblock_Line *ln1, *ln2;
   Evas_Object_Textblock_Item *it1, *it2;
   Eina_List *rects = NULL;
   Evas_Textblock_Rectangle *tr;

   if (!cur1 || !cur1->node) return NULL;
   if (!cur2 || !cur2->node) return NULL;
   if (cur1->obj != cur2->obj) return NULL;
   o = (Evas_Object_Textblock *)(cur1->obj->object_data);
   if (!o->formatted.valid) _relayout(cur1->obj);
   if (evas_textblock_cursor_compare(cur1, cur2) > 0)
     {
	const Evas_Textblock_Cursor *tc;

	tc = cur1;
	cur1 = cur2;
	cur2 = tc;
     }

   ln1 = ln2 = NULL;
   it1 = it2 = NULL;
   _find_layout_item_match(cur1, &ln1, &it1);
   if (!ln1 || !it1) return NULL;
   _find_layout_item_match(cur2, &ln2, &it2);
   if (!ln2 || !it2) return NULL;

   if (ln1 == ln2)
     {
        rects = _evas_textblock_cursor_range_in_line_geometry_get(ln1,
              cur1, cur2);
     }
   else
     {
        Evas_Object_Textblock_Line *plni, *lni;
        Eina_List *rects2 = NULL;

        rects = _evas_textblock_cursor_range_in_line_geometry_get(ln1,
              cur1, NULL);


        lni = (Evas_Object_Textblock_Line *) EINA_INLIST_GET(ln1)->next;
        if (!lni && (ln1->par != ln2->par))
          {
             lni = ((Evas_Object_Textblock_Paragraph *)
                    EINA_INLIST_GET(ln1->par)->next)->lines;
          }
        while (lni && (lni != ln2))
          {
	     tr = calloc(1, sizeof(Evas_Textblock_Rectangle));
	     rects = eina_list_append(rects, tr);
	     tr->x = lni->x;
	     tr->y = lni->par->y + lni->y;
	     tr->h = lni->h;
	     tr->w = lni->w;
             plni = lni;
             lni = (Evas_Object_Textblock_Line *) EINA_INLIST_GET(lni)->next;
             if (!lni && (plni->par != ln2->par))
               {
                  lni = ((Evas_Object_Textblock_Paragraph *)
                     EINA_INLIST_GET(plni->par)->next)->lines;
               }
          }
        rects2 = _evas_textblock_cursor_range_in_line_geometry_get(ln2,
              NULL, cur2);
        rects = eina_list_merge(rects, rects2);
     }
   return rects;
}
