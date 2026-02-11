p_status_progress(GapCmeGlobalParams *gpp, t_global_stb *gstb)
{
  GtkWidget  *pbar;
  GtkWidget  *status_lbl;


  status_lbl = gpp->cme__label_status;
  if(status_lbl)
  {
    gtk_label_set_text(GTK_LABEL(status_lbl), gstb->status_msg);
  }

  pbar = gpp->cme__progressbar_status;
  if(pbar)
  {
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR (pbar), gstb->progress);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), gstb->status_msg);
  }

  if(gap_debug) printf("progress: %f\n", (float)gstb->progress );
}
