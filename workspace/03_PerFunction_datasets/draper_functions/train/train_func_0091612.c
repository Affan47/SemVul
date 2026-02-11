freeverb_revmodel_free (GstFreeverb * filter)
{
  GstFreeverbPrivate *priv = filter->priv;
  gint i;

  for (i = 0; i < numcombs; i++) {
    freeverb_comb_release (&priv->combL[i]);
    freeverb_comb_release (&priv->combR[i]);
  }
  for (i = 0; i < numallpasses; i++) {
    freeverb_allpass_release (&priv->allpassL[i]);
    freeverb_allpass_release (&priv->allpassR[i]);
  }
}
