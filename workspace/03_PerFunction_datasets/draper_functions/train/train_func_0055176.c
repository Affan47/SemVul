e_dialog_icon_set(E_Dialog *dia, const char *icon, Evas_Coord size)
{
   if (!icon) return;

   dia->icon_object = e_icon_add(e_win_evas_get(dia->win));
   if (!e_util_icon_theme_set(dia->icon_object, icon))
     e_icon_file_edje_set(dia->icon_object, icon, "icon");
   edje_extern_object_min_size_set(dia->icon_object, size * e_scale, size * e_scale);
   edje_object_part_swallow(dia->bg_object, "e.swallow.icon", dia->icon_object);
   edje_object_signal_emit(dia->bg_object, "e,state,icon", "e");
   evas_object_show(dia->icon_object);
   if (icon)
     edje_object_signal_emit(dia->bg_object, "e,icon,enabled", "e");
   else
     edje_object_signal_emit(dia->bg_object, "e,icon,disabled", "e");
   edje_object_message_signal_process(dia->bg_object);
}
