e_gadcon_layout_pack_options_set(Evas_Object *obj, E_Gadcon_Client *gcc)
{
   int ok, seq;
   Eina_List *l;
   Evas_Object *item;
   E_Gadcon_Layout_Item *bi, *bi2;

   if (!obj) return;
   bi = evas_object_data_get(obj, "e_gadcon_layout_data");
   if (!bi) return;
   bi->ask.res = gcc->config.res;
   bi->ask.size = gcc->config.size;
   bi->ask.pos = gcc->config.pos;
   bi->gcc = gcc;

   ok = 0;
   if (!gcc->state_info.seq) ok = 1;

   seq = 1;
   EINA_LIST_FOREACH(bi->sd->items, l, item)
     {
        bi2 = evas_object_data_get(item, "e_gadcon_layout_data");
        if (bi == bi2) continue;
        if (bi->gcc->id == bi2->gcc->id) continue;
        if (bi->gcc->state_info.seq == bi2->gcc->state_info.seq)
          ok = 1;

        if (bi2->gcc->state_info.seq > seq)
          seq = bi2->gcc->state_info.seq;
     }

   if (ok)
     {
        gcc->state_info.seq = seq + 1;
        gcc->state_info.want_save = 1;
        gcc->state_info.flags = E_GADCON_LAYOUT_ITEM_LOCK_NONE;
     }
   _e_gadcon_layout_smart_reconfigure(bi->sd);
}
