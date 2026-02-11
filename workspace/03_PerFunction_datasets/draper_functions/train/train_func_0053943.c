on_details_updated (StatusMenu *self)
{
  status_menu_set_option (self, self->priv->personal_details->get_presence (), self->priv->personal_details->get_status ());
}
