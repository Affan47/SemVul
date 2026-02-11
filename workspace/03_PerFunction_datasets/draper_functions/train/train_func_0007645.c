showAlertMessage(GtkWidget *saveDialog, gchar* message, gboolean warning, int type)
{
  GtkWidget *wd;

  g_return_if_fail(type == VISU_CONFIG_FILE_RESOURCE ||
		   type == VISU_CONFIG_FILE_PARAMETER);
  g_return_if_fail(saveDialog);

  if (type == VISU_CONFIG_FILE_RESOURCE)
    wd = lookup_widget(saveDialog, "imageWarningResources");
  else
    wd = lookup_widget(saveDialog, "imageWarningParameters");
  if (warning)
    gtk_widget_show(wd);
  else
    gtk_widget_hide(wd);

  if (type == VISU_CONFIG_FILE_RESOURCE)
    {
      wd = lookup_widget(saveDialog, "statusbarResources");
      gtk_statusbar_pop(GTK_STATUSBAR(wd), saveResourcesContextId);
      gtk_statusbar_push(GTK_STATUSBAR(wd), saveResourcesContextId, message);
    }
  else
    {
      wd = lookup_widget(saveDialog, "statusbarParameters");
      gtk_statusbar_pop(GTK_STATUSBAR(wd), saveParametersContextId);
      gtk_statusbar_push(GTK_STATUSBAR(wd), saveParametersContextId, message);
    }
}
