cleanup_old_accounts_done (gpointer data)
{
  CleanupJob *job = data;
  GList *l;
  GoaObject *object;
  GomMiner *self = job->self;


  for (l = job->content_objects; l != NULL; l = l->next)
    {
      object = l->data;
      gom_miner_setup_account (self, object);

      g_object_unref (object);
    }

  if (job->content_objects != NULL)
    {
      g_list_free (job->content_objects);
      job->content_objects = NULL;
    }

  if (job->acc_objects != NULL)
    {
      g_list_free_full (job->acc_objects, g_object_unref);
      job->acc_objects = NULL;
    }

  if (job->old_datasources != NULL)
    {
      g_list_free_full (job->old_datasources, g_free);
      job->old_datasources = NULL;
    }

  gom_miner_check_pending_jobs (self);

  g_clear_object (&job->self);
  g_slice_free (CleanupJob, job);

  return FALSE;
}
