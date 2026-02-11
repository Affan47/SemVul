e_ilist_prepend_relative(Evas_Object *obj, Evas_Object *icon, Evas_Object *end, const char *label, int header, void (*func)(void *data, void *data2), void (*func_hilight)(void *data, void *data2), void *data, void *data2, int relative)
{
   E_Ilist_Item *si, *ri;
   Evas_Coord mw = 0, mh = 0;

   API_ENTRY return;
   si = _e_ilist_item_new(sd, icon, end, label, header, func, func_hilight, data, data2);

   ri = eina_list_nth(sd->items, relative);
   if (ri)
     sd->items = eina_list_prepend_relative(sd->items, si, ri);
   else
     sd->items = eina_list_prepend(sd->items, si);

   edje_object_size_min_calc(si->o_base, &mw, &mh);
   e_box_freeze(sd->o_box);
   if (ri)
     e_box_pack_before(sd->o_box, si->o_base, ri->o_base);
   else
     e_box_pack_end(sd->o_box, si->o_base);
   e_box_pack_options_set(si->o_base, 1, 1, 1, 1, 0.5, 0.5,
                          mw, mh, 99999, 99999);
   e_box_thaw(sd->o_box);

   evas_object_lower(sd->o_box);
   evas_object_show(si->o_base);
}
