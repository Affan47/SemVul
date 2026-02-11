clutter_actor_add_constraint_with_name (ClutterActor      *self,
                                        const gchar       *name,
                                        ClutterConstraint *constraint)
{
  g_return_if_fail (CLUTTER_IS_ACTOR (self));
  g_return_if_fail (name != NULL);
  g_return_if_fail (CLUTTER_IS_CONSTRAINT (constraint));

  clutter_actor_meta_set_name (CLUTTER_ACTOR_META (constraint), name);
  clutter_actor_add_constraint (self, constraint);
}
