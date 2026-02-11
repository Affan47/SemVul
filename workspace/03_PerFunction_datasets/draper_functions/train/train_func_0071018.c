_transit_effect_zoom_context_new(float from_rate, float to_rate)
{
   Elm_Transit_Effect_Zoom *zoom;

   zoom = ELM_NEW(Elm_Transit_Effect_Zoom);
   if (!zoom) return NULL;

   zoom->from = (_TRANSIT_FOCAL - (from_rate * _TRANSIT_FOCAL)) * (1 / from_rate);
   zoom->to = ((_TRANSIT_FOCAL - (to_rate * _TRANSIT_FOCAL)) * (1 / to_rate)) - zoom->from;

   return zoom;
}
