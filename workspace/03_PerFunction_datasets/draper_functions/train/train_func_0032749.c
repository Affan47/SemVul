udisks_base_job_get_property (GObject    *object,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{
  UDisksBaseJob *job = UDISKS_BASE_JOB (object);

  switch (prop_id)
    {
    case PROP_DAEMON:
      g_value_set_object (value, udisks_base_job_get_daemon (job));
      break;

    case PROP_CANCELLABLE:
      g_value_set_object (value, job->priv->cancellable);
      break;

    case PROP_AUTO_ESTIMATE:
      g_value_set_boolean (value, job->priv->auto_estimate);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
