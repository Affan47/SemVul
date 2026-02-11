udisks_base_job_set_property (GObject      *object,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspec)
{
  UDisksBaseJob *job = UDISKS_BASE_JOB (object);

  switch (prop_id)
    {
    case PROP_DAEMON:
      g_assert (job->priv->daemon == NULL);

      job->priv->daemon = g_value_get_object (value);
      break;

    case PROP_CANCELLABLE:
      g_assert (job->priv->cancellable == NULL);
      job->priv->cancellable = g_value_dup_object (value);
      break;

    case PROP_AUTO_ESTIMATE:
      udisks_base_job_set_auto_estimate (job, g_value_get_boolean (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
