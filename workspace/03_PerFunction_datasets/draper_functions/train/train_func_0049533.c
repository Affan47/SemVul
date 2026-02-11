reset_im_context (StIMText *self)
{
  StIMTextPrivate *priv = self->priv;

  if (priv->need_im_reset)
    {
      gtk_im_context_reset (priv->im_context);
      priv->need_im_reset = FALSE;
    }
}
