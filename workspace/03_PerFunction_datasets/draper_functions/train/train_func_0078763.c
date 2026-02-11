gap_cme_encoder_worker_thread(gpointer data)
{
  GapCmeGlobalParams *gpp;

  gpp = (GapCmeGlobalParams *) data;

  if(gap_debug)
  {
    printf("THREAD: gap_cme_encoder_worker_thread &gpp: %d\n", (int)gpp);
  }

  gap_cme_gui_start_video_encoder(gpp);

  if(gap_debug)
  {
    printf("THREAD gap_cme_encoder_worker_thread TERMINATING: %d\n", (int)gpp->val.gui_proc_thread);
  }

  gpp->productive_encoder_thread = NULL;

  return (NULL);
}
