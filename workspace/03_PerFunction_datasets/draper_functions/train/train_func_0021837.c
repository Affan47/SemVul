_string_check(void *data)
{
   Elm_Diskselector_Smart_Data *sd = data;
   int mid, steps, length, diff;
   Elm_Diskselector_Item *it;
   Eina_List *list, *l;
   Evas_Coord ox, ow;
   char buf[1024];

   evas_object_geometry_get(ELM_WIDGET_DATA(sd)->obj, &ox, NULL, &ow, NULL);

   if (ow <= 0)
     return EINA_FALSE;

   if (!sd->init)
     return EINA_FALSE;

   if (!sd->round)
     list = sd->items;
   else
     list = sd->r_items;

   EINA_LIST_FOREACH (list, l, it)
     {
        Evas_Coord x, w;
        int len;

        if (it->icon && !it->label)
          continue;

        evas_object_geometry_get(VIEW(it), &x, NULL, &w, NULL);

        if ((x + w <= ox) || (x >= ox + ow))
          continue;

        len = _letters_count(it->label);


        if (x <= ox + 5)
          edje_object_signal_emit(VIEW(it), "elm,state,left_side", "elm");
        else if (x + w >= ox + ow - 5)
          edje_object_signal_emit(VIEW(it), "elm,state,right_side", "elm");
        else
          {
             if ((sd->len_threshold) && (len > sd->len_threshold))
               edje_object_signal_emit
                 (VIEW(it), "elm,state,center_small", "elm");
             else
               edje_object_signal_emit(VIEW(it), "elm,state,center", "elm");
          }


        if (len <= sd->len_side)
          continue;

        steps = len - sd->len_side + 1;
        mid = x + w / 2;
        if (mid <= ox + ow / 2)
          diff = (ox + ow / 2) - mid;
        else
          diff = mid - (ox + ow / 2);

        length = len - (int)(diff * steps / (ow / 3));
        length = MAX(length, sd->len_side);

        length = _letters_check(it->label, length);

        strncpy(buf, it->label, length);
        buf[length] = '\0';
        edje_object_part_text_escaped_set(VIEW(it), "elm.text", buf);
     }

   if (sd->check_idler)
     ecore_idle_enterer_del(sd->check_idler);

   sd->check_idler = NULL;

   return EINA_FALSE;
}
