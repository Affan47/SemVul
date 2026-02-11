on_smiley_chooser_button_toggled (GtkToggleButton* toggle_button,
				  G_GNUC_UNUSED gpointer data)
{
  GmSmileyChooserButton* self = NULL;

  g_return_if_fail (GM_IS_SMILEY_CHOOSER_BUTTON (toggle_button));

  self = GM_SMILEY_CHOOSER_BUTTON (toggle_button);

  if (gtk_toggle_button_get_active (toggle_button))
    {

      gm_smiley_chooser_button_popup (self);
    }
  else
    {

      gm_smiley_chooser_button_popdown (self);
    }
}
