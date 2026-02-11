main (int argc, char *argv[])
{
  GError *error = NULL;


  ClutterActor *stage;
  ClutterLayoutManager *layout;
  ClutterActor *box;
  ClutterActor *top, *bottom;
  ClutterState *transitions;

  if (clutter_init_with_args (&argc, &argv,
                              " - cross-fade", entries,
                              NULL,
                              NULL) != CLUTTER_INIT_SUCCESS)
    return 1;

  if (source == NULL || target == NULL)
    {
      g_print ("Usage: %s -s <source> -t <target> [-d <duration>]\n", argv[0]);
      exit (EXIT_FAILURE);
    }

  if (clutter_init (&argc, &argv) != CLUTTER_INIT_SUCCESS)
    return 1;

  stage = clutter_stage_new ();
  clutter_stage_set_title (CLUTTER_STAGE (stage), "cross-fade");
  clutter_actor_set_size (stage, 400, 300);
  clutter_actor_show (stage);
  g_signal_connect (stage, "destroy", G_CALLBACK (clutter_main_quit), NULL);

  layout = clutter_bin_layout_new (CLUTTER_BIN_ALIGNMENT_CENTER,
                                   CLUTTER_BIN_ALIGNMENT_CENTER);

  box = clutter_box_new (layout);
  clutter_actor_set_size (box, 400, 300);

  bottom = clutter_texture_new ();
  top = clutter_texture_new ();

  clutter_container_add_actor (CLUTTER_CONTAINER (box), bottom);
  clutter_container_add_actor (CLUTTER_CONTAINER (box), top);
  clutter_container_add_actor (CLUTTER_CONTAINER (stage), box);


  load_image (CLUTTER_TEXTURE (bottom), source);


  load_image (CLUTTER_TEXTURE (top), target);


  transitions = clutter_state_new ();
  clutter_state_set (transitions, NULL, "show-bottom",
                     top, "opacity", CLUTTER_LINEAR, 0,
                     bottom, "opacity", CLUTTER_LINEAR, 255,
                     NULL);
  clutter_state_set (transitions, NULL, "show-top",
                     top, "opacity", CLUTTER_EASE_IN_CUBIC, 255,
                     bottom, "opacity", CLUTTER_EASE_IN_CUBIC, 0,
                     NULL);
  clutter_state_set_duration (transitions, NULL, NULL, duration);


  clutter_state_warp_to_state (transitions, "show-bottom");


  g_signal_connect (stage,
                    "key-press-event",
                    G_CALLBACK (start_animation),
                    transitions);

  clutter_actor_show (stage);

  clutter_main ();

  g_object_unref (transitions);

  if (error != NULL)
    g_error_free (error);

  return EXIT_SUCCESS;
}
