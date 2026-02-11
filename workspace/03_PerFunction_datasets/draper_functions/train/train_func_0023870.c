_item_icon_set(Elm_Diskselector_Item *it,
               Evas_Object *icon)
{
   if (it->icon == icon) return;

   if (it->icon) evas_object_del(it->icon);
   it->icon = icon;
   if (VIEW(it))
     {

        if (it->icon && (!it->label))
          edje_object_signal_emit(VIEW(it), "elm,state,icon,only", "elm");

        evas_object_size_hint_min_set(it->icon, 24, 24);
        evas_object_size_hint_max_set(it->icon, 40, 40);
        edje_object_part_swallow(VIEW(it), "elm.swallow.icon", it->icon);
        evas_object_show(it->icon);
        elm_widget_sub_object_add(WIDGET(it), it->icon);
     }
}
