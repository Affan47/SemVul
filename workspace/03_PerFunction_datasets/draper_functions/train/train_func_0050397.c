test_destroy_destroy (ClutterActor *self)
{
  TestDestroy *test = TEST_DESTROY (self);

  if (test->bg != NULL)
    {
      if (g_test_verbose ())
        g_print ("Destroying '%s' (type:%s)\n",
                 clutter_actor_get_name (test->bg),
                 G_OBJECT_TYPE_NAME (test->bg));

      clutter_actor_destroy (test->bg);
      test->bg = NULL;
    }

  if (test->label != NULL)
    {
      if (g_test_verbose ())
        g_print ("Destroying '%s' (type:%s)\n",
                 clutter_actor_get_name (test->label),
                 G_OBJECT_TYPE_NAME (test->label));

      clutter_actor_destroy (test->label);
      test->label = NULL;
    }

  if (test->tex != NULL)
    {
      if (g_test_verbose ())
        g_print ("Destroying '%s' (type:%s)\n",
                 clutter_actor_get_name (test->tex),
                 G_OBJECT_TYPE_NAME (test->tex));

      clutter_actor_destroy (test->tex);
      test->tex = NULL;
    }

  g_list_foreach (test->children, (GFunc) clutter_actor_destroy, NULL);
  g_list_free (test->children);
  test->children = NULL;

  if (CLUTTER_ACTOR_CLASS (test_destroy_parent_class)->destroy)
    CLUTTER_ACTOR_CLASS (test_destroy_parent_class)->destroy (self);
}
