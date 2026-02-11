update_label (TpawCalendarButton *self)
{
  if (self->priv->date == NULL)
    {
      gtk_button_set_label (GTK_BUTTON (self->priv->button_date),
          _("Select..."));
    }
  else
    {
      gchar buffer[128];

      g_date_strftime (buffer, 128, "%e %b %Y", self->priv->date);
      gtk_button_set_label (GTK_BUTTON (self->priv->button_date), buffer);
    }
}
