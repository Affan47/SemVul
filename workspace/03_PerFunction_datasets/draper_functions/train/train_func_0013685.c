_elm_scroll_gravity_get(const Evas_Object *obj,
                        double *x,
                        double *y)
{
   ELM_SCROLL_IFACE_DATA_GET_OR_RETURN(obj, sid);

   if (!sid->pan_obj) return;

   ELM_PAN_DATA_GET_OR_RETURN(sid->pan_obj, psd);

   psd->api->gravity_get(sid->pan_obj, x, y);
}
