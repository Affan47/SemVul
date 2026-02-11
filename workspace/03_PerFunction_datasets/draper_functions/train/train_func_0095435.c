mx_adjustment_dispose (GObject *object)
{
  MxAdjustmentPrivate *priv = MX_ADJUSTMENT (object)->priv;

  stop_interpolation (MX_ADJUSTMENT (object));


  mx_adjustment_remove_idle (&priv->value_source);
  mx_adjustment_remove_idle (&priv->lower_source);
  mx_adjustment_remove_idle (&priv->upper_source);
  mx_adjustment_remove_idle (&priv->page_inc_source);
  mx_adjustment_remove_idle (&priv->step_inc_source);
  mx_adjustment_remove_idle (&priv->page_size_source);
  mx_adjustment_remove_idle (&priv->changed_source);

  if (priv->interpolate_alpha)
    {
      g_object_unref (priv->interpolate_alpha);
      priv->interpolate_alpha = NULL;
    }

  G_OBJECT_CLASS (mx_adjustment_parent_class)->dispose (object);
}
