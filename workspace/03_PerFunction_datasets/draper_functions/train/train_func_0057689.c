_decorate_all_set_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info __UNUSED__)
{
   if (!data) return;

   Evas_Object *gl;
   gl = evas_object_data_get(obj, "gl");
   if (!gl) return;

   if (evas_object_data_get(gl, "tree_effect"))
     elm_genlist_tree_effect_enabled_set(gl, EINA_FALSE);
   elm_genlist_decorate_mode_set(gl, EINA_TRUE);
}
