_signal_add_show(E_Config_Dialog_Data *cfdata)
{
   Evas_Object *o, *obg, *ol, *entry;
   Evas *evas;
   int w, h;

   if (cfdata->locals.dia) return;

   cfdata->locals.dia = e_dialog_new(NULL, "E", "_signalbind_new_dialog");
   e_dialog_resizable_set(cfdata->locals.dia, 1);
   e_dialog_title_set(cfdata->locals.dia, _("Add Signal Binding"));
   e_dialog_icon_set(cfdata->locals.dia, "enlightenment/signals", 48);
   e_dialog_button_add(cfdata->locals.dia, _("OK"), NULL, _signal_add_cb_ok, cfdata);
   e_dialog_button_add(cfdata->locals.dia, _("Cancel"), NULL, _signal_add_cb_cancel, cfdata);
   e_object_del_attach_func_set(E_OBJECT(cfdata->locals.dia), _signal_add_del);
   cfdata->locals.dia->data = cfdata;
   e_win_centered_set(cfdata->locals.dia->win, 1);

   evas = e_win_evas_get(cfdata->locals.dia->win);
   obg = e_widget_list_add(evas, 1, 0);

   ol = e_widget_framelist_add(evas, _("Source:"), 0);
   entry = o = e_widget_entry_add(evas, &cfdata->locals.dia_source, NULL, NULL, NULL);
   e_widget_framelist_object_append(ol, o);
   e_widget_list_object_append(obg, ol, 1, 0, 0.5);

   ol = e_widget_framelist_add(evas, _("Signal:"), 0);
   o = e_widget_entry_add(evas, &cfdata->locals.dia_signal, NULL, NULL, NULL);
   e_widget_framelist_object_append(ol, o);
   e_widget_list_object_append(obg, ol, 1, 0, 0.5);

   e_widget_size_min_get(obg, &w, &h);
   e_dialog_content_set(cfdata->locals.dia, obg, MAX(w, 200), MAX(h, 100));

   e_dialog_show(cfdata->locals.dia);
   e_widget_focus_set(entry, 1);
   e_dialog_parent_set(cfdata->locals.dia, cfdata->cfd->dia->win);
}
