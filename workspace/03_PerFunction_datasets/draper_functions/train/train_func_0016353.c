e_obj_dialog_new(E_Container *con, char *title, char *class_name, char *class_class)
{
   E_Obj_Dialog *od;
   E_Manager *man;
   Evas_Object *o;

   if (!con)
     {
	man = e_manager_current_get();
	if (!man) return NULL;
	con = e_container_current_get(man);
	if (!con) con = e_container_number_get(man, 0);
	if (!con) return NULL;
     }
   od = E_OBJECT_ALLOC(E_Obj_Dialog, E_OBJ_DIALOG_TYPE, _e_obj_dialog_free);
   if (!od) return NULL;
   od->win = e_win_new(con);
   if (!od->win)
     {
	free(od);
	return NULL;
     }
   e_win_delete_callback_set(od->win, _e_obj_dialog_cb_delete);
   e_win_resize_callback_set(od->win, _e_obj_dialog_cb_resize);
   od->win->data = od;
   e_win_dialog_set(od->win, 1);
   e_win_name_class_set(od->win, class_name, class_class);
   e_win_title_set(od->win, title);

   o = edje_object_add(e_win_evas_get(od->win));
   od->bg_object = o;

   e_win_centered_set(od->win, 1);
   od->cb_delete = NULL;

   return od;
}
