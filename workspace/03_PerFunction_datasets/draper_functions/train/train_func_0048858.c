main (int argc, char *argv[])
{
  ClutterActor *view, *stage;
  ChamplainMarkerLayer *layer;
  SoupSession *session;

  if (clutter_init (&argc, &argv) != CLUTTER_INIT_SUCCESS)
    return 1;

  stage = clutter_stage_new ();
  clutter_actor_set_size (stage, 800, 600);
  g_signal_connect (stage, "destroy", G_CALLBACK (clutter_main_quit), NULL);


  view = champlain_view_new ();
  clutter_actor_set_size (CLUTTER_ACTOR (view), 800, 600);
  clutter_actor_add_child (stage, view);


  layer = champlain_marker_layer_new_full (CHAMPLAIN_SELECTION_SINGLE);
  champlain_view_add_layer (CHAMPLAIN_VIEW (view), CHAMPLAIN_LAYER (layer));
  session = soup_session_async_new ();
  create_marker_from_url (layer, session, 48.218611, 17.146397,
      "http://hexten.net/cpan-faces/potyl.jpg");
  create_marker_from_url (layer, session, 48.21066, 16.31476,
      "http://hexten.net/cpan-faces/jkutej.jpg");
  create_marker_from_url (layer, session, 48.14838, 17.10791,
      "http://bratislava.pm.org/images/whoiswho/jnthn.jpg");


  g_object_set (G_OBJECT (view), "zoom-level", 10,
      "kinetic-mode", TRUE, NULL);
  champlain_view_center_on (CHAMPLAIN_VIEW (view), 48.22, 16.8);

  clutter_actor_show (stage);
  clutter_main ();

  g_object_unref (session);

  return 0;
}
