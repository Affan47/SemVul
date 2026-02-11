fill_we_protocols_tab(World *world, GtkBuilder *ui_builder)
{
  GObject *rad;

  if (!world) {
    return;
  }

  if (world->mccp_behavior == MCCP_DISABLE) {
    rad = gtk_builder_get_object(ui_builder, "radMCCPDisable");
  } else if (world->mccp_behavior == MCCP_ALWAYS) {
    rad = gtk_builder_get_object(ui_builder, "radMCCPAlways");
  } else {
    rad = gtk_builder_get_object(ui_builder, "radMCCPAfterConnect");
  }

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rad), TRUE);
}
