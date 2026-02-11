_activate(Elm_Fileselector_Button_Smart_Data *sd)
{
   Eina_Bool is_inwin = EINA_FALSE;

   if (sd->fs) return;

   if (sd->inwin_mode)
     {
        sd->fsw = _parent_win_get(ELM_WIDGET_DATA(sd)->obj);

        if (!sd->fsw)
          sd->fsw = _new_window_add(sd);
        else
          {
             sd->fsw = elm_win_inwin_add(sd->fsw);
             is_inwin = EINA_TRUE;
          }
     }
   else
     sd->fsw = _new_window_add(sd);

   sd->fs = elm_fileselector_add(sd->fsw);
   elm_widget_mirrored_set
     (sd->fs, elm_widget_mirrored_get(ELM_WIDGET_DATA(sd)->obj));
   elm_widget_mirrored_automatic_set(sd->fs, EINA_FALSE);
   elm_fileselector_expandable_set(sd->fs, sd->fsd.expandable);
   elm_fileselector_folder_only_set(sd->fs, sd->fsd.folder_only);
   elm_fileselector_is_save_set(sd->fs, sd->fsd.is_save);
   elm_fileselector_selected_set(sd->fs, sd->fsd.path);
   evas_object_size_hint_weight_set
     (sd->fs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(sd->fs, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_smart_callback_add(sd->fs, "done", _selection_done, sd);
   evas_object_show(sd->fs);

   if (is_inwin)
     {
        elm_win_inwin_content_set(sd->fsw, sd->fs);
        elm_win_inwin_activate(sd->fsw);
     }
   else
     {
        elm_win_resize_object_add(sd->fsw, sd->fs);
        evas_object_show(sd->fsw);
     }
}
