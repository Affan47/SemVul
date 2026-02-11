wait_for_pdf_save_pending_thread ()
{
  if (pdf_data->thread)
    {
      g_thread_join (pdf_data->thread);
      pdf_data->thread = NULL;
    }
}
