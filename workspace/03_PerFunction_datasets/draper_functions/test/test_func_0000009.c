_transit_effect_wipe_context_free(Elm_Transit_Effect *effect, Elm_Transit *transit)
{
   EINA_SAFETY_ON_NULL_RETURN(effect);
   EINA_SAFETY_ON_NULL_RETURN(transit);
   Eina_List *elist;
   Evas_Object *obj;
   Elm_Transit_Effect_Wipe *wipe = effect;
   Eina_Bool reverse = elm_transit_auto_reverse_get(transit);

   EINA_LIST_FOREACH(transit->objs, elist, obj)
     {
        if ((wipe->type == ELM_TRANSIT_EFFECT_WIPE_TYPE_SHOW && !reverse)
            || (wipe->type == ELM_TRANSIT_EFFECT_WIPE_TYPE_HIDE && reverse))
          evas_object_show(obj);
        else evas_object_hide(obj);
        evas_object_map_enable_set(obj, EINA_FALSE);
     }

   free(wipe);
}
