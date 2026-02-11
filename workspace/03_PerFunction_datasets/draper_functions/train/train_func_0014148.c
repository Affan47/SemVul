sync_global_resources(GObject *object _U_, VisuData *dataObj _U_,
				  gpointer data _U_)
{
  float spherical[3], cartesian[3], wheel;
  int i;

  DBG_fprintf(stderr, "Gtk Spin: caught the 'resourcesLoaded' signal.\n");

  if(gtkw_cone_theta_angle == NULL)
    return;

  spherical[0] = 1;
  g_object_get(G_OBJECT(visu_rendering_getByName(VISU_RENDERING_SPIN_NAME)),
               "cone-theta", spherical + 1, "cone-phi", spherical + 2,
               "cone-omega", &wheel, NULL);

  tool_matrix_sphericalToCartesian(cartesian, spherical);

  for(i=0; i<3; i++)
    if(cartesian[i] < 0.01 && cartesian [i] > -0.01)
      cartesian[i] = 0;

  need_redraw = 0;

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtkw_x), cartesian[0]);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtkw_y), cartesian[1]);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtkw_z), cartesian[2]);

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtkw_cone_theta_angle), spherical[1]);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtkw_cone_phi_angle), spherical[2]);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtkw_color_wheel_angle), wheel);

  need_redraw = 1;
}
