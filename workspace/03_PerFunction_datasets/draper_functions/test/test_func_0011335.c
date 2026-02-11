elm_genlist_bounce_get(const Evas_Object *obj,
                       Eina_Bool *h_bounce,
                       Eina_Bool *v_bounce)
{
   ELM_GENLIST_CHECK(obj);
   ELM_GENLIST_DATA_GET(obj, sd);

   if (h_bounce) *h_bounce = sd->h_bounce;
   if (v_bounce) *v_bounce = sd->v_bounce;
}
