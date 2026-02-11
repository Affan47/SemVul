clutter_actor_real_get_paint_volume (ClutterActor       *self,
                                     ClutterPaintVolume *volume)
{
  ClutterActorClass *klass;
  gboolean res;

  klass = CLUTTER_ACTOR_GET_CLASS (self);


  if (klass->paint == clutter_actor_real_paint &&
      klass->get_paint_volume == clutter_actor_real_get_paint_volume)
    {
      res = TRUE;
    }
  else
    {


      res = FALSE;
    }


  if (!clutter_actor_update_default_paint_volume (self, volume))
    return FALSE;

  return res;
}
