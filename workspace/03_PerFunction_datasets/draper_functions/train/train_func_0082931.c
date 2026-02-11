_class_list_load(E_Config_Dialog_Data *cfdata)
{
   Evas *evas;
   Eina_List *next;

   if (!cfdata->gui.class_list) return;
   evas = evas_object_evas_get(cfdata->gui.class_list);
   evas_event_freeze(evas);
   edje_freeze();
   e_widget_ilist_freeze(cfdata->gui.class_list);
   e_widget_ilist_clear(cfdata->gui.class_list);


   for (next = cfdata->text_classes; next; next = next->next)
     {
        CFText_Class *tc;
        Evas_Object *ic;

        tc = next->data;
        if (tc)
          {
             if (tc->class_name)
               {
                  if (tc->enabled)
                    {
                       ic = e_icon_add(evas);
                       e_util_icon_theme_set(ic, "dialog-ok-apply");
                    }
                  else
                    ic = NULL;
                  e_widget_ilist_append(cfdata->gui.class_list, ic, tc->class_description, NULL, tc, NULL);
               }
             else
               e_widget_ilist_header_append(cfdata->gui.class_list, NULL, tc->class_description);
          }
     }
   e_widget_ilist_go(cfdata->gui.class_list);
   e_widget_ilist_thaw(cfdata->gui.class_list);
   edje_thaw();
   evas_event_thaw(evas);
}
