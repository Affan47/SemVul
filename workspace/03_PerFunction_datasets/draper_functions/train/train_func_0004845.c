actor_mapped (TestConformSimpleFixture *fixture,
              gconstpointer             data)
{
  ClutterActor *actor;
  ClutterActor *stage;

  stage = clutter_stage_new ();
  clutter_actor_show (stage);

  actor = clutter_actor_new ();

  g_assert (!(CLUTTER_ACTOR_IS_REALIZED (actor)));
  g_assert (!(CLUTTER_ACTOR_IS_MAPPED (actor)));

  clutter_actor_add_child (stage, actor);

  if (g_test_verbose ())
    g_print ("adding to a container should map - "
             "visible: %s, realized: %s, mapped: %s\n",
             CLUTTER_ACTOR_IS_VISIBLE (actor) ? "yes" : "no",
             CLUTTER_ACTOR_IS_REALIZED (actor) ? "yes" : "no",
             CLUTTER_ACTOR_IS_MAPPED (actor) ? "yes" : "no");

  g_assert (CLUTTER_ACTOR_IS_REALIZED (actor));
  g_assert (CLUTTER_ACTOR_IS_MAPPED (actor));
  g_assert (CLUTTER_ACTOR_IS_VISIBLE (actor));

  clutter_actor_hide (actor);

  if (g_test_verbose ())
    g_print ("hiding should unmap - "
             "visible: %s, realized: %s, mapped: %s\n",
             CLUTTER_ACTOR_IS_VISIBLE (actor) ? "yes" : "no",
             CLUTTER_ACTOR_IS_REALIZED (actor) ? "yes" : "no",
             CLUTTER_ACTOR_IS_MAPPED (actor) ? "yes" : "no");

  g_assert (CLUTTER_ACTOR_IS_REALIZED (actor));
  g_assert (!CLUTTER_ACTOR_IS_MAPPED (actor));
  g_assert (!CLUTTER_ACTOR_IS_VISIBLE (actor));

  clutter_actor_destroy (stage);
}
