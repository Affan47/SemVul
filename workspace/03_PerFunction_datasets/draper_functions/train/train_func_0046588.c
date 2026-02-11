gdu_application_create_local_job  (GduApplication *application,
                                   UDisksObject   *object)
{
  GduLocalJob *job = NULL;
  GList *local_jobs;

  g_return_val_if_fail (GDU_IS_APPLICATION (application), NULL);
  g_return_val_if_fail (UDISKS_IS_OBJECT (object), NULL);

  job = gdu_local_job_new (object);

  local_jobs = g_hash_table_lookup (application->local_jobs, object);
  local_jobs = g_list_prepend (local_jobs, job);
  g_hash_table_insert (application->local_jobs, object, local_jobs);

  g_signal_connect (job, "notify", G_CALLBACK (on_local_job_notify), application);

  udisks_client_queue_changed (application->client);

  return job;
}
