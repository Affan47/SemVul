_but_edit(void *d1,
          void *d2)
{
   E_Config_Dialog *cfd = d1;
   Evas_Object *il = d2;
   int n;
   Match_Config *m;

   n = e_widget_ilist_selected_get(il);
   m = e_widget_ilist_nth_data_get(il, n);
   if (!m) return;

   cfd->cfdata->edit_il = il;
   _create_edit_frame(cfd, evas_object_evas_get(il), cfd->cfdata, m);
   cfd->cfdata->match.changed = 1;
}
