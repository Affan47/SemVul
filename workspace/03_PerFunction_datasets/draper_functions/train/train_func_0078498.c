theme_free_toplevel(struct theme *t)
{
  if (t->font_filename) {
    FC_FREE(t->font_filename);
  }

  t->default_font_size = 0;

  if (t->background_system) {
    theme_background_system_free(t->background_system);
    t->background_system = NULL;
  }

  if (t->color_system) {
    theme_color_system_free(t->color_system);
    t->color_system = NULL;
  }
}
