fallback_provider_remove (AdwaitaEngine *self)
{
  GdkScreen *screen;

  if (self->fallback_provider == NULL)
    return;

  screen = gdk_screen_get_default ();
  gtk_style_context_remove_provider_for_screen
    (screen, GTK_STYLE_PROVIDER (self->fallback_provider));
  g_clear_object (&self->fallback_provider);
}
