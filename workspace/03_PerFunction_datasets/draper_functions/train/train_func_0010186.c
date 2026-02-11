clutter_check_windowing_backend (const char *backend_type)
{
  ClutterMainContext *context = _clutter_context_get_default ();

  g_return_val_if_fail (backend_type != NULL, FALSE);

  backend_type = g_intern_string (backend_type);

#ifdef CLUTTER_WINDOWING_OSX
  if (backend_type == I_(CLUTTER_WINDOWING_OSX) &&
      CLUTTER_IS_BACKEND_OSX (context->backend))
    return TRUE;
  else
#endif
#ifdef CLUTTER_WINDOWING_WIN32
  if (backend_type == I_(CLUTTER_WINDOWING_WIN32) &&
      CLUTTER_IS_BACKEND_WIN32 (context->backend))
    return TRUE;
  else
#endif
#ifdef CLUTTER_WINDOWING_WAYLAND
  if (backend_type == I_(CLUTTER_WINDOWING_WAYLAND) &&
      CLUTTER_IS_BACKEND_WAYLAND (context->backend))
    return TRUE;
  else
#endif
#ifdef CLUTTER_WINDOWING_EGL
  if (backend_type == I_(CLUTTER_WINDOWING_EGL) &&
      CLUTTER_IS_BACKEND_EGL_NATIVE (context->backend))
    return TRUE;
  else
#endif
#ifdef CLUTTER_WINDOWING_GDK
  if (backend_type == I_(CLUTTER_WINDOWING_GDK) &&
      CLUTTER_IS_BACKEND_GDK (context->backend))
    return TRUE;
  else
#endif
#ifdef CLUTTER_WINDOWING_X11
  if (backend_type == I_(CLUTTER_WINDOWING_X11) &&
      CLUTTER_IS_BACKEND_X11 (context->backend))
    return TRUE;
  else
#endif
  return FALSE;
}
