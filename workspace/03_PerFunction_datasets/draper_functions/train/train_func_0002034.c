_e_gadcon_layout_smart_gadcons_asked_position_set(E_Smart_Data *sd)
{
   E_Gadcon_Layout_Item *bi;
   Eina_List *l;
   Evas_Object *item;

#if 0
   EINA_LIST_FOREACH(sd->items, l, item)
     {
        bi = evas_object_data_get(item, "e_gadcon_layout_data");
        if (!bi) continue;

        bi->x = bi->ask.pos;
        bi->w = bi->ask.size2;
     }
#else
   int pos;
   EINA_LIST_FOREACH(sd->items, l, item)
     {
        bi = evas_object_data_get(item, "e_gadcon_layout_data");
        if (!bi) continue;

        pos = bi->ask.pos + (bi->ask.size / 2);
        if (pos < (bi->ask.res / 3))
          {

             bi->x = bi->ask.pos;
             bi->w = bi->ask.size2;
             bi->hookp = 0;
          }
        else if (pos > ((2 * bi->ask.res) / 3))
          {

             bi->x = (bi->ask.pos - bi->ask.res) + sd->w;
             bi->w = bi->ask.size2;
             bi->hookp = bi->ask.res;
          }
        else
          {

             if ((bi->ask.pos <= (bi->ask.res / 2)) &&
                 ((bi->ask.pos + bi->ask.size2) > (bi->ask.res / 2)))
               {

                  if (bi->ask.res > 2)
                    bi->x = (sd->w / 2) +
                      (((bi->ask.pos + (bi->ask.size2 / 2) -
                         (bi->ask.res / 2)) *
                        (bi->ask.res / 2)) /
                       (bi->ask.res / 2)) - (bi->ask.size2 / 2);
                  else
                    bi->x = sd->w / 2;
                  bi->w = bi->ask.size2;
               }
             else
               {

                  bi->x = (bi->ask.pos - (bi->ask.res / 2)) + (sd->w / 2);
                  bi->w = bi->ask.size2;
               }
             bi->hookp = bi->ask.res / 2;
          }
     }
#endif
}
