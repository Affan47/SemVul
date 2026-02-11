_elm_win_on_parent_del(void *data,
                       Evas *e __UNUSED__,
                       Evas_Object *obj,
                       void *event_info __UNUSED__)
{
   Elm_Win_Smart_Data *sd = data;

   if (obj == sd->parent) sd->parent = NULL;
}
