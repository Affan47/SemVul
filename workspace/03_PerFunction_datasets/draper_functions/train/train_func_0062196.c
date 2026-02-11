queue_start_process (struct BrowseRelayCb *brc)
{
  QueueElement *qelement;

  if (!brc->dispatcher_running) {
    qelement = g_queue_peek_head (brc->queue);
    if (qelement && qelement->is_ready) {
      guint id = g_idle_add (queue_process,  brc);
      g_source_set_name_by_id (id, "[grilo] queue_process");
      brc->dispatcher_running = TRUE;
    }
  }
}
