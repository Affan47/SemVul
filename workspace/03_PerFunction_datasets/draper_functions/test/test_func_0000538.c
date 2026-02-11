story_dlg_destroy (GtkWidget *widget,
                 GapStbMainGlobalParams *sgpp_1)
{
  GtkWidget *dialog;
  GapStbMainGlobalParams *sgpp;

  dialog = NULL;

  if(sgpp_1 != NULL)
  {
    sgpp = sgpp_1;
  }
  else
  {
    sgpp = (GapStbMainGlobalParams *)g_object_get_data(G_OBJECT(widget), "sgpp");
  }


  if(sgpp)
  {
    gap_story_vthumb_close_videofile(sgpp);
    dialog = sgpp->shell_window;
    if(dialog)
    {
      sgpp->shell_window = NULL;
      gtk_widget_destroy (dialog);
    }
  }

  gtk_main_quit ();

}
