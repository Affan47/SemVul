unico_register_style_default (UnicoStyleFunctions *functions)
{
  g_assert (functions);

  functions->draw_arrow    = unico_draw_arrow;
  functions->draw_expander = unico_draw_expander;
  functions->draw_focus    = unico_draw_focus;
}
