elm_table_homogeneous_set(Evas_Object *obj,
                          Eina_Bool homogeneous)
{
   ELM_TABLE_CHECK(obj);
   ELM_TABLE_DATA_GET(obj, sd);

   evas_object_table_homogeneous_set
     (ELM_WIDGET_DATA(sd)->resize_obj, homogeneous);
}
