elm_layout_part_cursor_style_set(Evas_Object *obj,
                                 const char *part_name,
                                 const char *style)
{
   ELM_LAYOUT_CHECK(obj) EINA_FALSE;
   ELM_LAYOUT_DATA_GET_OR_RETURN_VAL(obj, sd, EINA_FALSE);
   EINA_SAFETY_ON_NULL_RETURN_VAL(part_name, EINA_FALSE);

   Elm_Layout_Sub_Object_Cursor *pc = _parts_cursors_find(sd, part_name);
   EINA_SAFETY_ON_NULL_RETURN_VAL(pc, EINA_FALSE);
   EINA_SAFETY_ON_NULL_RETURN_VAL(pc->obj, EINA_FALSE);

   eina_stringshare_replace(&pc->style, style);
   elm_object_cursor_style_set(pc->obj, pc->style);

   return EINA_TRUE;
}
