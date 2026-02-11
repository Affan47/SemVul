setRenderingSpecificWidget(struct RenderingExpanderWidget_struct *str)
{
  GtkWidget *wd;


  wd = gtk_bin_get_child(GTK_BIN(viewport));
  if (wd)
    {
      if (currentDestroyFunc)
      	currentDestroyFunc();
      gtk_widget_destroy(wd);
    }

  if (str && str->create)
    {
      DBG_fprintf(stderr, "Panel Method: creating the rendering specific"
		  " widget for current method.\n");
      wd = str->create();
      currentDestroyFunc = str->destroy;
    }
  else
    {
      DBG_fprintf(stderr, "Panel Method: no rendering specific"
		  " widget for the current method.\n");
      wd = gtk_label_new("");
      gtk_label_set_markup(GTK_LABEL(wd), _("<i>None</i>"));
      gtk_misc_set_alignment(GTK_MISC(wd), 0., 0.);
      gtk_misc_set_padding(GTK_MISC(wd), 15, 0);
      currentDestroyFunc = (VisuUiPanelDestroyFunc)0;
    }
  gtk_container_add(GTK_CONTAINER(viewport), wd);
  gtk_widget_show(wd);
}
