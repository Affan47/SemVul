gap_navigator(gint32 image_id)
{
  GtkWidget *shell;
  GtkWidget *subshell;

  if(gap_debug) fprintf(stderr, "\nSTARTing gap_navigator_dialog\n");

  gimp_ui_init ("gap_navigator", FALSE);
  gap_stock_init();


  shell = gimp_dialog_new (_("Video Navigator"), "gap_navigator",
                           NULL, 0,
                           gimp_standard_help_func, PLUGIN_HELP_ID,

                           GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE,

                           NULL
                           );


  subshell = gtk_vbox_new (FALSE, 1);
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG (shell)->vbox), subshell);

  if(gap_debug) printf("BEFORE  navi_dialog_create\n");


  navi_dialog_create (shell, image_id);
  if(gap_debug) printf("AFTER  navi_dialog_create\n");

  gtk_box_pack_start (GTK_BOX (subshell), naviD->vbox, TRUE, TRUE, 0);

  gtk_widget_show (subshell);
  gtk_widget_show (shell);

  frames_dialog_flush();
  navi_scroll_to_current_frame_nr();

  naviD->timer = g_timeout_add (naviD->cycle_time,
                                (GtkFunction)navi_dialog_poll, NULL);


  naviD->in_dyn_table_sizeinit = FALSE;

  if(gap_debug) printf("BEFORE  gimp_dialog_run\n");

  gimp_dialog_run (GIMP_DIALOG (shell));

  if (naviD->timer >= 0)
    {
      g_source_remove(naviD->timer);
      naviD->timer = -1;
    }

  navi_pviews_reset();

  gtk_widget_destroy (shell);

  if(gap_debug) printf("END gap_navigator_dialog\n");

  return 0;
}
