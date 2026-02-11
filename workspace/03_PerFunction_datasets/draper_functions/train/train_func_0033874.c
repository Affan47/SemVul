_clutter_create_backend (void)
{
  const char *backend = allowed_backend;
  ClutterBackend *retval = NULL;

  if (backend == NULL)
    {
      const char *backend_env = g_getenv ("CLUTTER_BACKEND");

      if (backend_env != NULL)
	backend = g_intern_string (backend_env);
    }

#ifdef CLUTTER_WINDOWING_OSX
  if (backend == NULL || backend == I_(CLUTTER_WINDOWING_OSX))
    retval = g_object_new (CLUTTER_TYPE_BACKEND_OSX, NULL);
  else
#endif
#ifdef CLUTTER_WINDOWING_WIN32
  if (backend == NULL || backend == I_(CLUTTER_WINDOWING_WIN32))
    retval = g_object_new (CLUTTER_TYPE_BACKEND_WIN32, NULL);
  else
#endif
#ifdef CLUTTER_WINDOWING_X11
  if (backend == NULL || backend == I_(CLUTTER_WINDOWING_X11))
    retval = g_object_new (CLUTTER_TYPE_BACKEND_X11, NULL);
  else
#endif
#ifdef CLUTTER_WINDOWING_WAYLAND
  if (backend == NULL || backend == I_(CLUTTER_WINDOWING_WAYLAND))
    retval = g_object_new (CLUTTER_TYPE_BACKEND_WAYLAND, NULL);
  else
#endif
#ifdef CLUTTER_WINDOWING_EGL
  if (backend == NULL || backend == I_(CLUTTER_WINDOWING_EGL))
    retval = g_object_new (CLUTTER_TYPE_BACKEND_EGL_NATIVE, NULL);
  else
#endif
#ifdef CLUTTER_WINDOWING_GDK
  if (backend == NULL || backend == I_(CLUTTER_WINDOWING_GDK))
    retval = g_object_new (CLUTTER_TYPE_BACKEND_GDK, NULL);
  else
#endif
  if (backend == NULL)
    g_error ("No default Clutter backend found.");
  else
    g_error ("Unsupported Clutter backend: '%s'", backend);

  return retval;
}
