gtk_clutter_actor_show (ClutterActor *self)
{
  GtkClutterActorPrivate *priv = GTK_CLUTTER_ACTOR (self)->priv;
  GtkWidget *widget = gtk_bin_get_child (GTK_BIN (priv->widget));

  CLUTTER_ACTOR_CLASS (gtk_clutter_actor_parent_class)->show (self);


  if (widget != NULL)
    gtk_widget_show (widget);
}
