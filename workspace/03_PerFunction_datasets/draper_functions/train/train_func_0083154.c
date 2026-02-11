on_toplevel_hide (G_GNUC_UNUSED GtkWidget* window,
		  gpointer data)
{
  GmSmileyChooserButton* self = NULL;

  g_return_if_fail (GM_IS_SMILEY_CHOOSER_BUTTON (data));

  self = GM_SMILEY_CHOOSER_BUTTON (data);

  gm_smiley_chooser_button_popdown (self);
}
