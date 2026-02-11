_access_obj_del(void *data __UNUSED__, Evas *e __UNUSED__,
                Evas_Object *obj, void *event_info __UNUSED__)
{
   char *part = evas_object_data_get(obj, "_elm_access_part");
   evas_object_data_del(obj, "_elm_access_part");
   if (part) free(part);
}
