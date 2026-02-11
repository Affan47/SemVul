updateFilterLabel() {
  char z[256];
  g_strlcpy(z,_("Filter: "),256);
  g_strlcat(z,inner->Filter.getString(),256);
  if (strlen(z)==strlen(_("Filter: ")))
    g_strlcat(z,_("(none)"),256);
  gtk_label_set_text(GTK_LABEL(flabel),z);
  gtk_widget_queue_resize(flabel);
}
