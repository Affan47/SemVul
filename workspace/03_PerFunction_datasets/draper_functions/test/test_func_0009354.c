mx_path_bar_crumb_clicked_cb (ClutterActor *crumb,
                              MxPathBar    *self)
{
  gint i;
  GList *c;

  MxPathBarPrivate *priv = self->priv;

  if (priv->clear_on_change)
    mx_path_bar_set_text (self, "");

  for (c = priv->crumbs, i = 1; c; c = c->next, i++)
    {
      if (c->data == crumb)
        {
          while (priv->current_level > i)
            mx_path_bar_pop (self);
          break;
        }
    }
}
