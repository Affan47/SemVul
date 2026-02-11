elm_frame_autocollapse_set(Evas_Object *obj,
                           Eina_Bool autocollapse)
{
   ELM_FRAME_CHECK(obj);
   ELM_FRAME_DATA_GET_OR_RETURN(obj, sd);

   sd->collapsible = !!autocollapse;
}
