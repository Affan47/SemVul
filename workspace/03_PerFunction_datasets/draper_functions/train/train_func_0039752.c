_ilist_path_cb_change(void *data)
{
   CFPath_Change_Data *pcd;
   Eina_List *default_list;
   Eina_List *l;

   pcd = data;
   default_list = pcd->path->default_dir_list;


   evas_event_freeze(evas_object_evas_get(pcd->cfdata->gui.default_list));
   edje_freeze();
   e_widget_ilist_freeze(pcd->cfdata->gui.default_list);

   e_widget_ilist_clear(pcd->cfdata->gui.default_list);
   for (l = default_list; l; l = l->next)
     {
	const char *dir;

	dir = ((E_Path_Dir *)l->data)->dir;
	e_widget_ilist_append(pcd->cfdata->gui.default_list,
			      NULL, dir, NULL, NULL, NULL);
     }
   e_widget_ilist_go(pcd->cfdata->gui.default_list);

   e_widget_ilist_thaw(pcd->cfdata->gui.default_list);
   edje_thaw();
   evas_event_thaw(evas_object_evas_get(pcd->cfdata->gui.default_list));

   _ilist_update(pcd->cfdata->gui.user_list,
		 pcd->cfdata->cur_pcd,
		 pcd);

   pcd->cfdata->cur_pcd = pcd;
}
