elm_smart_scroller_single_dir_set(Evas_Object *obj, Eina_Bool single_dir)
{
   API_ENTRY return;
   sd->one_dir_at_a_time = single_dir;
}
