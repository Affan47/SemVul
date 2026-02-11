clutter_x11_set_use_argb_visual (gboolean use_argb)
{
  if (_clutter_context_is_initialized ())
    {
      g_warning ("%s() can only be used before calling clutter_init()",
                 G_STRFUNC);
      return;
    }

  CLUTTER_NOTE (BACKEND, "ARGB visuals are %s",
                use_argb ? "enabled" : "disabled");

  clutter_enable_argb = use_argb;
}
