exo_job_emit_valist (ExoJob *job,
                     guint   signal_id,
                     GQuark  signal_detail,
                     va_list var_args)
{
  ExoJobSignalData data;

  _exo_return_if_fail (EXO_IS_JOB (job));
  _exo_return_if_fail (job->priv->scheduler_job != NULL);

  data.instance = job;
  data.signal_id = signal_id;
  data.signal_detail = signal_detail;


  G_VA_COPY (data.var_args, var_args);


  g_io_scheduler_job_send_to_mainloop (job->priv->scheduler_job,
                                       exo_job_emit_valist_in_mainloop,
                                       &data, NULL);
}
