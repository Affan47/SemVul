emit_completed_with_error_in_idle (UDisksSpawnedJob *job,
                                   GError           *error)
{
  EmitCompletedData *data;
  GSource *idle_source;

  g_return_if_fail (UDISKS_IS_SPAWNED_JOB (job));
  g_return_if_fail (error != NULL);

  data = g_new0 (EmitCompletedData, 1);
  data->job = g_object_ref (job);
  data->error = g_error_copy (error);
  idle_source = g_idle_source_new ();
  g_source_set_priority (idle_source, G_PRIORITY_DEFAULT);
  g_source_set_callback (idle_source,
                         emit_completed_with_error_in_idle_cb,
                         data,
                         NULL);
  g_source_attach (idle_source, job->main_context);
  g_source_unref (idle_source);
}
