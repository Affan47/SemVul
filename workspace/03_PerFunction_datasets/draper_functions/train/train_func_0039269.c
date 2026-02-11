foo_button_clicked_cb (ClutterClickAction *action,
                       ClutterActor       *actor,
                       gpointer            user_data)
{
  gfloat z_angle;


  ClutterScript *ui = CLUTTER_SCRIPT (user_data);


  ClutterActor *rectangle;
  clutter_script_get_objects (ui,
                              "rectangle", &rectangle,
                              NULL);


  if (clutter_actor_get_animation (rectangle) != NULL)
    return;


  z_angle = clutter_actor_get_rotation (rectangle,
                                        CLUTTER_Z_AXIS,
                                        NULL, NULL, NULL);

  if (clutter_click_action_get_button (action) == 1)
    z_angle += 90.0;
  else
    z_angle -= 90.0;


  clutter_actor_animate (rectangle,
                         CLUTTER_EASE_OUT_CUBIC,
                         1000,
                         "rotation-angle-z", z_angle,
                         NULL);
}
