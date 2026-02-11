_layout_last_line_max_descent_adjust_calc(Ctxt *c, const Evas_Object_Textblock_Paragraph *last_vis_par)
{
   if (last_vis_par->lines)
     {
        Evas_Coord maxdescent = 0, descent = 0;
        Evas_Object_Textblock_Line *ln = (Evas_Object_Textblock_Line *)
           EINA_INLIST_GET(last_vis_par->lines)->last;
        Evas_Object_Textblock_Item *it;

        EINA_INLIST_FOREACH(ln->items, it)
          {
             if (it->type == EVAS_TEXTBLOCK_ITEM_TEXT)
               {
                  Evas_Coord asc = 0, desc = 0;
                  Evas_Coord masc = 0, mdesc = 0;
                  _layout_item_ascent_descent_adjust(c->obj, &asc, &desc,
                        it, c->position);
                  _layout_item_max_ascent_descent_calc(c->obj, &masc, &mdesc,
                        it, c->position);

                  if (desc > descent)
                     descent = desc;
                  if (mdesc > maxdescent)
                     maxdescent = mdesc;
               }
          }

        if (maxdescent > descent)
          {
             return maxdescent - descent;
          }
     }

   return 0;
}
