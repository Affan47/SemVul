clutter_actor_real_pick (ClutterActor       *self,
			 const ClutterColor *color)
{


  if (clutter_actor_should_pick_paint (self))
    {
      ClutterActorBox box = { 0, };
      float width, height;

      clutter_actor_get_allocation_box (self, &box);

      width = box.x2 - box.x1;
      height = box.y2 - box.y1;

      cogl_set_source_color4ub (color->red,
                                color->green,
                                color->blue,
                                color->alpha);

      cogl_rectangle (0, 0, width, height);
    }


  if (CLUTTER_ACTOR_GET_CLASS (self)->pick == clutter_actor_real_pick)
    {
      ClutterActor *iter;

      for (iter = self->priv->first_child;
           iter != NULL;
           iter = iter->priv->next_sibling)
        clutter_actor_paint (iter);
    }
}
