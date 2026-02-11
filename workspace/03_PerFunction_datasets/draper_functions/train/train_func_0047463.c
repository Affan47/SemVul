elm_datetime_field_visible_get(const Evas_Object *obj,
                               Elm_Datetime_Field_Type fieldtype)
{
   Datetime_Field *field;
   ELM_DATETIME_CHECK(obj) EINA_FALSE;
   ELM_DATETIME_DATA_GET(obj, sd);

   if (fieldtype > ELM_DATETIME_AMPM) return EINA_FALSE;

   field = sd->field_list + fieldtype;

   return field->visible;
}
