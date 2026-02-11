exo_job_async_ready (gpointer user_data)
{
  ExoJob *job = EXO_JOB (user_data);

  _exo_return_val_if_fail (EXO_IS_JOB (job), FALSE);

  if (job->priv->failed)
    {
      g_assert (job->priv->error != NULL);


      if (!g_error_matches (job->priv->error, G_IO_ERROR, G_IO_ERROR_CANCELLED))
        exo_job_error (job, job->priv->error);


      g_error_free (job->priv->error);
      job->priv->error = NULL;
    }

  exo_job_finished (job);

  job->priv->running = FALSE;

  return FALSE;
}
