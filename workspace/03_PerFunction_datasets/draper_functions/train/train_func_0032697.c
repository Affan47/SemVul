_cb_adv_btn_clearall(void *data1, void *data2 __UNUSED__)
{
   E_Config_Dialog_Data *cfdata;
   E_Config_Theme *t;
   Eina_List *themes;
   Evas_Object *oc = NULL, *of = NULL;
   int n, cnt;

   if (!(cfdata = data1)) return;

   if (!(oc = cfdata->o_categories_ilist)) return;
   if (!(of = cfdata->o_files_ilist)) return;

   cnt = e_widget_ilist_count(oc);
   for (n = 0; n < cnt; n++)
     e_widget_ilist_nth_icon_set(oc, n, NULL);

   cnt = e_widget_ilist_count(of);
   for (n = 0; n < cnt; n++)
     e_widget_ilist_nth_icon_set(of, n, NULL);

   EINA_LIST_FOREACH(cfdata->theme_list, themes, t)
     {
        eina_stringshare_del(t->file);
        t->file = NULL;
     }

   return;
}
