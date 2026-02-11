refresh_update_button (CcInfoPanel  *self)
{
  GtkWidget *widget;

  widget = WID ("updates_button");
  if (widget == NULL)
    return;

  switch (self->priv->updates_state)
    {
      case PK_NOT_AVAILABLE:
        gtk_widget_set_visible (widget, FALSE);
        break;
      case UPDATES_AVAILABLE:
        gtk_widget_set_sensitive (widget, TRUE);
        gtk_button_set_label (GTK_BUTTON (widget), _("Install Updates"));
        break;
      case UPDATES_NOT_AVAILABLE:
        gtk_widget_set_sensitive (widget, FALSE);
        gtk_button_set_label (GTK_BUTTON (widget), _("System Up-To-Date"));
        break;
      case CHECKING_UPDATES:
        gtk_widget_set_sensitive (widget, FALSE);
        gtk_button_set_label (GTK_BUTTON (widget), _("Checking for Updates"));
        break;
    }
}
