onShowMainPanel(VisuUiMain *main, VisuUiRenderingWindow *window _U_)
{
  if (main->private->actionDialogIsShown)
    gtk_window_present(GTK_WINDOW(main->interactiveDialog));
  else
    gtk_window_present(GTK_WINDOW(main));
}
