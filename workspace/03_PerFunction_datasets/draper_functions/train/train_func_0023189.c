mx_spinner_timeout_cb (MxSpinner *spinner)
{
  MxSpinnerPrivate *priv = spinner->priv;


  clutter_actor_queue_redraw (CLUTTER_ACTOR (spinner));

  if (++priv->current_frame == priv->frames)
    {
      priv->current_frame = 0;
      g_signal_emit (spinner, signals[LOOPED], 0);
    }

  return TRUE;
}
