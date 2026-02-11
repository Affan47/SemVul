_dlg_add_new(E_Config_Dialog_Data *cfdata)
{
   E_Dialog *dlg;
   Evas *evas;
   Evas_Coord mw, mh;
   Evas_Object *mainn;

   if (!(dlg = e_dialog_new(_xkb.cfd->con, "E", "xkbswitch_config_add_dialog"))) return NULL;

   e_dialog_resizable_set(dlg, 1);
   dlg->data = cfdata;

   e_object_del_attach_func_set(E_OBJECT(dlg), _dlg_add_cb_del);
   e_win_centered_set(dlg->win, 1);

   evas = e_win_evas_get(dlg->win);
   e_dialog_title_set(dlg, _("Add New Configuration"));


   mainn = e_widget_toolbook_add(evas, 24, 24);
   {

      Evas_Object *available = e_widget_ilist_add(evas, 32, 32, NULL);
      Evas_Object *modelss;
      Evas_Object *variants;

      {
         e_widget_size_min_set(available, 220, 160);
         e_widget_ilist_go(available);
         e_widget_toolbook_page_append(mainn, NULL, _("Available"), available, 1, 1, 1, 1, 0.5, 0.0);
         cfdata->layout_list = available;
      }


      modelss = e_widget_ilist_add(evas, 32, 32, NULL);
      {
         e_widget_toolbook_page_append(mainn, NULL, _("Model"), modelss, 1, 1, 1, 1, 0.5, 0.0);
         cfdata->model_list = modelss;
      }


      variants = e_widget_ilist_add(evas, 32, 32, NULL);
      {
         e_widget_toolbook_page_append(mainn, NULL, _("Variant"), variants, 1, 1, 1, 1, 0.5, 0.0);
         cfdata->variant_list = variants;
      }
      e_widget_toolbook_page_show(mainn, 0);
   }

   e_widget_size_min_get(mainn, &mw, &mh);
   e_dialog_content_set(dlg, mainn, mw, mh);

   cfdata->dlg_evas = evas;


   if (cfdata->dlg_fill_delay) ecore_timer_del(cfdata->dlg_fill_delay);


   cfdata->dlg_fill_delay = ecore_timer_add(0.2, _cb_dlg_fill_delay, cfdata);


   e_dialog_button_add(dlg, _("OK"), NULL, _dlg_add_cb_ok, cfdata);
   e_dialog_button_add(dlg, _("Cancel"), NULL, _dlg_add_cb_cancel, cfdata);

   e_dialog_button_disable_num_set(dlg, 0, 1);
   e_dialog_button_disable_num_set(dlg, 1, 0);

   e_dialog_show(dlg);

   return dlg;
}
