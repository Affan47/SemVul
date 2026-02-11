_size_native_calc_paragraph_size(const Evas_Object *obj,
      const Evas_Object_Textblock *o,
      const Evas_Object_Textblock_Paragraph *par,
      Textblock_Position *position,
      Evas_Coord *_w, Evas_Coord *_h)
{
   Eina_List *i;
   Evas_Object_Textblock_Item *it;
   Eina_List *line_items = NULL;
   Evas_Coord w = 0, y = 0, wmax = 0, h = 0, ascent = 0, descent = 0;

   EINA_LIST_FOREACH(par->logical_items, i, it)
     {
        line_items = eina_list_append(line_items, it);
        if (it->type == EVAS_TEXTBLOCK_ITEM_FORMAT)
          {
             Evas_Object_Textblock_Format_Item *fi = _ITEM_FORMAT(it);
             if (fi->item && (_IS_LINE_SEPARATOR(fi->item) ||
                      _IS_PARAGRAPH_SEPARATOR(o, fi->item)))
               {
                  _size_native_calc_line_finalize(obj, line_items, &ascent,
                        &descent, &w, *position);

                  if (ascent + descent > h)
                     h = ascent + descent;

                  y += h;
                  if (w > wmax)
                     wmax = w;
                  h = 0;
                  ascent = descent = 0;
                  *position = TEXTBLOCK_POSITION_ELSE;
                  line_items = eina_list_free(line_items);
               }
             else
               {
                  Evas_Coord fw, fh, fy;


                  if (it && (ascent + descent == 0))
                     _layout_item_ascent_descent_adjust(obj, &ascent,
                           &descent, it, *position);

                  _layout_calculate_format_item_size(obj, fi, &ascent,
                        &descent, &fy, &fw, &fh);
               }
          }
        else
          {
             _layout_item_ascent_descent_adjust(obj, &ascent,
                   &descent, it, *position);
          }
     }

   if (!EINA_INLIST_GET(par)->next)
     {
        *position = (*position == TEXTBLOCK_POSITION_START) ?
           TEXTBLOCK_POSITION_SINGLE : TEXTBLOCK_POSITION_END;
     }
   _size_native_calc_line_finalize(obj, line_items, &ascent, &descent, &w, *position);

   if (*position == TEXTBLOCK_POSITION_START)
      *position = TEXTBLOCK_POSITION_ELSE;

   line_items = eina_list_free(line_items);


   if (ascent + descent > h)
      h = ascent + descent;

   if (w > wmax)
      wmax = w;

   *_h = y + h;
   *_w = wmax;
}
