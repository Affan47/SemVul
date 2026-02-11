_transit_effect_color_op(Elm_Transit_Effect *effect, Elm_Transit *transit, double progress)
{
   EINA_SAFETY_ON_NULL_RETURN(effect);
   EINA_SAFETY_ON_NULL_RETURN(transit);
   Elm_Transit_Effect_Color *color = effect;
   Evas_Object *obj;
   Eina_List *elist;
   unsigned int r, g, b, a;

   r = (color->from.r + (int)((float)color->to.r * progress));
   g = (color->from.g + (int)((float)color->to.g * progress));
   b = (color->from.b + (int)((float)color->to.b * progress));
   a = (color->from.a + (int)((float)color->to.a * progress));

   EINA_LIST_FOREACH(transit->objs, elist, obj)
     evas_object_color_set(obj, r, g, b, a);
}
