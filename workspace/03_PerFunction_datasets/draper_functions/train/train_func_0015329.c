egg_list_box_set_activate_on_single_click (EggListBox *list_box,
					   gboolean single)
{
  EggListBoxPrivate *priv = list_box->priv;

  g_return_if_fail (list_box != NULL);

  single = single != FALSE;

  if (priv->activate_single_click == single)
    return;

  priv->activate_single_click = single;

  g_object_notify_by_pspec (G_OBJECT (list_box), properties[PROP_ACTIVATE_ON_SINGLE_CLICK]);
}
