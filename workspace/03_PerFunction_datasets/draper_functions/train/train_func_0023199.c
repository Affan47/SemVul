_transit_effect_flip_context_free(Elm_Transit_Effect *effect, Elm_Transit *transit)
{
   EINA_SAFETY_ON_NULL_RETURN(effect);
   EINA_SAFETY_ON_NULL_RETURN(transit);
   Elm_Transit_Effect_Flip *flip = effect;
   Evas_Object *front, *back;
   int i;
   int count = eina_list_count(transit->objs);

   for (i = 0; i < (count - 1); i += 2)
     {
        front = eina_list_nth(transit->objs, i);
        back = eina_list_nth(transit->objs, i+1);
        evas_object_map_enable_set(front, EINA_FALSE);
        evas_object_map_enable_set(back, EINA_FALSE);
     }
   free(flip);
}
