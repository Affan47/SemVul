elm_gengrid_bounce_set(Evas_Object *obj,
                       Eina_Bool h_bounce,
                       Eina_Bool v_bounce)
{
   ELM_GENGRID_CHECK(obj);
   ELM_GENGRID_DATA_GET(obj, sd);

   sd->s_iface->bounce_allow_set(obj, !!h_bounce, !!v_bounce);
}
